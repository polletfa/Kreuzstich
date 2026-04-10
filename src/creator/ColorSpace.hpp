#ifndef COLORSPACE_HPP
#define COLORSPACE_HPP

class ColorSpace {
public:
    ColorSpace() = delete; // utility class - static methods only

    /**
     * (s)RGBA color space
     */
    struct rgba_t {
        double red{1};
        double green{1};
        double blue{1};
        double alpha{1};
    };

    /**
     * HSL color space (for sorting)
     */
    struct hsl_t {
        double hue;
        double saturation;
        double lightness;
    };

    /**
     * CIELAB colorspace (for distance)
     * D65 standard illuminant - 2° observer (CIE 1931)
     */
    struct lab_t {
        double lightness;
        double a;          /**< green <-> red axis */
        double b;          /**< blue <-> yellow axis */
    };

    /**
     * Convert RGBA to simple RGB (a = 100%) by using the specified background color.
     */
    static rgba_t compositeRGBAOntoBackground(const rgba_t& rgba, const rgba_t& bg);

    /**
     * Convert RGBA to HSL
     * If alpha is not 100%, assume white background (@see compositeRGBAOntoBackground)
     *
     * See:
     * - https://en.wikipedia.org/wiki/HSL_and_HSV
     */
    static hsl_t toHSL(const rgba_t& rgba);

    /**
     * Convert RGBA to CIELAB using standard illuminant D65 and 2° observer (CIE1931)
     * If alpha is not 100%, assume white background (@see compositeRGBAOntoBackground)
     *
     * See:
     * - http://www.brucelindbloom.com/
     * - https://en.wikipedia.org/wiki/CIELAB_color_space
     */
    static lab_t toLAB(const rgba_t& rgba);

    enum DistanceAlgo { CIE1976, CIEDE2000 }; /**< Algorithms for distance computation */

    /**
     * Compute the distance between two colors in the LAB space using CIEDE2000
     *
     * See:
     * - http://www.brucelindbloom.com/
     */
    static double distance(const lab_t& color1, const lab_t& color2, DistanceAlgo algo = CIEDE2000);

private:
    constexpr static double toRadians(double degrees);
};

#endif // COLORSPACE_HPP
