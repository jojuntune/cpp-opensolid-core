from string import Template

comparison_operator_list = ['==', '!=', '<', '>', '<=', '>=']
arithmetic_operator_list = ['unary-', '+', '-', '*', '/']
function_list = ['min', 'max']
operator_list = comparison_operator_list + arithmetic_operator_list + function_list
builtin_type_list = ['int', 'float', 'double']
custom_type_list = ['Double', 'Interval']

header = open('operators.hpp', 'w')

def signature(operator, first_type, second_type):
    global comparison_operator_list, function_list
    return_type = None
    if operator in comparison_operator_list:
        return_type = 'bool'
    elif 'Interval' in (first_type, second_type):
        return_type = 'Interval'
    else:
        return_type = 'Double'
    function_name = operator if operator in function_list else 'operator' + operator
    template = Template(
        '$return_type ' +
        '$function_name($first_type first_argument, $second_type second_argument)'
    )
    return template.substitute(locals())
    
def write_declaration(operator, first_type, second_type):
    global header
    if operator == '-' and second_type is None:
        header.write(' ' * 4 + first_type + ' operator-(' + first_type + ' argument);\n')
    else:
        header.write(' ' * 4 + signature(operator, first_type, second_type) + ';\n')
    
def write_definition(operator, first_type, second_type):
    global header
    if operator == '-' and second_type is None:
        header.write(
            ' ' * 4 + 'inline ' + first_type + ' operator-(' + first_type + ' argument) ' +
                '{return -argument.value();}\n'
        )
    else:
        global comparison_operator_list, function_list, builtin_type_list, custom_type_list
        header.write(' ' * 4 + 'inline ' + signature(operator, first_type, second_type) + ' {\n')
        first_value = 'first_argument' + ('.value()' if first_type in custom_type_list else '')
        second_value = 'second_argument' + ('.value()' if second_type in custom_type_list else '')
        result = None  
        if 'Interval' in (first_type, second_type) and operator in comparison_operator_list:
            first_lower = first_value + ('.lower()' if first_type == 'Interval' else '')
            first_upper = first_value + ('.upper()' if first_type == 'Interval' else '')
            second_lower = second_value + ('.lower()' if second_type == 'Interval' else '')
            second_upper = second_value + ('.upper()' if second_type == 'Interval' else '')
            template = None
            if operator == '==':
                result = Template(
                    '$first_lower == $second_lower &&\n' + ' ' * 12 + '$first_upper == $second_upper'
                ).substitute(locals())
            elif operator == '!=':
                result = Template(
                    '$first_lower != $second_lower ||\n' + ' ' * 12 + '$first_upper != $second_upper'
                ).substitute(locals())
            else:
                result = Template(
                    '$first_lower == $second_lower ?\n' +
                    ' ' * 12  + '$first_upper $operator $second_upper :\n' +
                    ' ' * 12  + '$first_lower $operator $second_lower'
                ).substitute(locals())
        else:
            if 'Interval' in (first_type, second_type) or operator in function_list:
                if first_type in ['int', 'float']:
                    first_value = 'double(' + first_value + ')'
                elif second_type in ['int', 'float']:
                    second_value = 'double(' + second_value + ')'
            if operator in function_list:
                result = operator + '(' + first_value + ', ' + second_value + ')'
            else:
                result = first_value + ' ' + operator + ' ' + second_value
                
        # elif 'Interval' in (first_type, second_type) or operator in function_list:
        #     prefix = None
        #     specialization = None
        #     if 'Interval' in (first_type, second_type):
        #         prefix = 'boost::numeric'
        #         specialization = 'double, IntervalPolicies'
        #     else:
        #         prefix = 'std'
        #         specialization = 'double'
        #     name = operator if operator in function_list else 'operator' + operator
        #     full_name = prefix + '::' + name + '<' + specialization + '>'
        #     if 'Interval' in (first_type, second_type):
        #         lines = [
        #             full_name + '(',
        #             ' ' * 12 + first_value + ',',
        #             ' ' * 12 + second_value,
        #             ' ' * 8 + ')'
        #         ]
        #         result = '\n'.join(lines)
        #     else:
        #         result = full_name + '(' + first_value + ', ' + second_value + ')'
        # else:
        #     result = first_value + ' ' + operator + ' ' + second_value
            
        header.write(' ' * 8 + 'return ' + result + ';\n')
        header.write(' ' * 4 + '}\n')
    
def write_all(write_function):
    global comparison_operator_list, arithmetic_operator_list, operator_list
    global builtin_type_list, custom_type_list
    global header
    for operator in operator_list:
        for custom_type in custom_type_list:
            if operator == 'unary-':
                if custom_type == 'Double':
                    header.write('\n')
                write_function('-', custom_type, None)
                if custom_type == 'Double' and write_function is write_definition:
                    header.write('\n')
            else:
                header.write('\n')
                write_function(operator, custom_type, custom_type)
                if write_function is write_definition:
                    header.write('\n')
                other_type = (set(custom_type_list) - set([custom_type])).pop()
                write_function(operator, custom_type, other_type)
                if write_function is write_definition:
                    header.write('\n')
                for builtin_type in builtin_type_list:
                    write_function(operator, custom_type, builtin_type)
                    if write_function is write_definition:
                        header.write('\n')
                    write_function(operator, builtin_type, custom_type)

header.write("""
/***************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                   *
 *   ian.e.mackenzie@gmail.com                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef OPENSOLID__SCALAR__OPERATORS_HPP
#define OPENSOLID__SCALAR__OPERATORS_HPP

// This file is generated by operators.py - do not modify.

#include <algorithm>
#include <boost/numeric/interval.hpp>

namespace OpenSolid
{
    using std::min;
    using std::max;
    using boost::numeric::min;
    using boost::numeric::max;

    class Double;
    class Interval;
""")
    
write_all(write_declaration)
                
header.write("""}

////////// Implementation //////////

#include <OpenSolid/Scalar/Double.hpp>
#include <OpenSolid/Scalar/Interval.hpp>

namespace OpenSolid
{""")

write_all(write_definition)

header.write("""}

#endif\n
""")             
