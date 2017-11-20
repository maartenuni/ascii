
#include<cstdint>

#define POINTS_PER_INCH (72.0)


double points_to_pixels(double point, double resolution)
{
    return point * resolution / POINTS_PER_INCH;
}

double pixels_to_points(double pixel, double resolution)
{
    return pixel / (resolution / POINTS_PER_INCH);
}

int64_t
round_font_unit(int64_t fu)
{
    return (fu + 32) & -64;
}    

int64_t
floor_font_unit(int64_t fu)
{
    return fu & -64;
}

int64_t
ceil_font_unit(int64_t fu)
{
    return (fu + 64) & -64;
}    
