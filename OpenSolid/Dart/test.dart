import 'opensolid.dart';

main() {
    var zero = new Zero();
    print("first precision: ${zero.precision}");

    var zero2 = new Zero(1e-3);
    print("second precision: ${zero2.precision}");
}
