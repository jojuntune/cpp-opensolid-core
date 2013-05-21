namespace OpenSolid
{
    public static class OpenSolidExtensions
    {
        public static bool IsZero(this double value, double precision = 1e-12)
        {
            return value >= -precision && value <= precision;
        }

        public static bool IsNotZero(this double value, double precision = 1e-12)
        {
            return value < -precision || value > precision;
        }

        public static bool IsLessThanZero(this double value, double precision = 1e-12)
        {
            return value < -precision;
        }

        public static bool IsGreaterThanZero(this double value, double precision = 1e-12)
        {
            return value > precision;
        }

        public static bool IsLessThanOrEqualToZero(this double value, double precision = 1e-12)
        {
            return value <= precision;
        }

        public static bool IsGreaterThanOrEqualToZero(this double value, double precision = 1e-12)
        {
            return value >= -precision;
        }
    }
}
