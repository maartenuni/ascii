
#ifndef FONT_UTILS_H
#define FONT_UTILS_H

#include<cstdint>

/**
 * Convert from a measure in points to a measure in pixels
 *
 * \param [in] point_size the size of a font 1/72th of an inch
 * \param [in] resolution the resolution of the font in inches.
 *
 * \return a number of pixels
 */
double points_to_pixels(double point_size, double resolution);

/**
 * Convert from a measure in pixels to a measure in font points 1/72 of an inch
 *
 * \param [in] the size in pixels.
 * \param [in] resolution the resolution of the font in inches.
 *
 * \return a number of pixels
 */
double pixels_to_points(double pixel_size, double resolution);

/**
 * rounds a font_unit.
 */
int64_t round_font_unit(int64_t fu);

/**
 * Floors a font unit
 */
int64_t floor_font_unit(int64_t fu);

/**
 * Ceil a font unit
 */
int64_t ceil_font_unit(int64_t fu);

#endif//ifndef FONT_UTILS_H
