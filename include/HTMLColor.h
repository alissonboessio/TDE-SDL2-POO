#ifndef HTML_COLOR_H
#define HTML_COLOR_H

#include <string>
#include <unordered_map>
#include "Primitives.h"

class RGBA {
    public :

        unsigned int r, g, b, a;

};

class HtmlColor {
private:
    static RGBA hexToRGBA(const std::string& hex) {
        RGBA rgba;
        if (hex[0] == '#') {
            sscanf(hex.c_str() + 1, "%02x%02x%02x", &rgba.r, &rgba.g, &rgba.b);
        } else {
            sscanf(hex.c_str(), "%02x%02x%02x", &rgba.r, &rgba.g, &rgba.b);
        }
        //Uint32 a = 0xFF;
        // return (r << 24) | (g << 16) | (b << 8) | a;
        // return (r << 16) | (g << 8) | b;

        rgba.a = 0;
        return rgba;

    }

    // ===== Inicialização da tabela com todas as 140 cores HTML =====
    inline static std::unordered_map<std::string, RGBA> colorMap = {
        {"aliceblue", HtmlColor::hexToRGBA("#F0F8FF")},
        {"antiquewhite", HtmlColor::hexToRGBA("#FAEBD7")},
        {"aqua", HtmlColor::hexToRGBA("#00FFFF")},
        {"aquamarine", HtmlColor::hexToRGBA("#7FFFD4")},
        {"azure", HtmlColor::hexToRGBA("#F0FFFF")},
        {"beige", HtmlColor::hexToRGBA("#F5F5DC")},
        {"bisque", HtmlColor::hexToRGBA("#FFE4C4")},
        {"black", HtmlColor::hexToRGBA("#000000")},
        {"blanchedalmond", HtmlColor::hexToRGBA("#FFEBCD")},
        {"blue", HtmlColor::hexToRGBA("#0000FF")},
        {"blueviolet", HtmlColor::hexToRGBA("#8A2BE2")},
        {"brown", HtmlColor::hexToRGBA("#A52A2A")},
        {"burlywood", HtmlColor::hexToRGBA("#DEB887")},
        {"cadetblue", HtmlColor::hexToRGBA("#5F9EA0")},
        {"chartreuse", HtmlColor::hexToRGBA("#7FFF00")},
        {"chocolate", HtmlColor::hexToRGBA("#D2691E")},
        {"coral", HtmlColor::hexToRGBA("#FF7F50")},
        {"cornflowerblue", HtmlColor::hexToRGBA("#6495ED")},
        {"cornsilk", HtmlColor::hexToRGBA("#FFF8DC")},
        {"crimson", HtmlColor::hexToRGBA("#DC143C")},
        {"cyan", HtmlColor::hexToRGBA("#00FFFF")},
        {"darkblue", HtmlColor::hexToRGBA("#00008B")},
        {"darkcyan", HtmlColor::hexToRGBA("#008B8B")},
        {"darkgoldenrod", HtmlColor::hexToRGBA("#B8860B")},
        {"darkgray", HtmlColor::hexToRGBA("#A9A9A9")},
        {"darkgreen", HtmlColor::hexToRGBA("#006400")},
        {"darkkhaki", HtmlColor::hexToRGBA("#BDB76B")},
        {"darkmagenta", HtmlColor::hexToRGBA("#8B008B")},
        {"darkolivegreen", HtmlColor::hexToRGBA("#556B2F")},
        {"darkorange", HtmlColor::hexToRGBA("#FF8C00")},
        {"darkorchid", HtmlColor::hexToRGBA("#9932CC")},
        {"darkred", HtmlColor::hexToRGBA("#8B0000")},
        {"darksalmon", HtmlColor::hexToRGBA("#E9967A")},
        {"darkseagreen", HtmlColor::hexToRGBA("#8FBC8F")},
        {"darkslateblue", HtmlColor::hexToRGBA("#483D8B")},
        {"darkslategray", HtmlColor::hexToRGBA("#2F4F4F")},
        {"darkturquoise", HtmlColor::hexToRGBA("#00CED1")},
        {"darkviolet", HtmlColor::hexToRGBA("#9400D3")},
        {"deeppink", HtmlColor::hexToRGBA("#FF1493")},
        {"deepskyblue", HtmlColor::hexToRGBA("#00BFFF")},
        {"dimgray", HtmlColor::hexToRGBA("#696969")},
        {"dodgerblue", HtmlColor::hexToRGBA("#1E90FF")},
        {"firebrick", HtmlColor::hexToRGBA("#B22222")},
        {"floralwhite", HtmlColor::hexToRGBA("#FFFAF0")},
        {"forestgreen", HtmlColor::hexToRGBA("#228B22")},
        {"fuchsia", HtmlColor::hexToRGBA("#FF00FF")},
        {"gainsboro", HtmlColor::hexToRGBA("#DCDCDC")},
        {"ghostwhite", HtmlColor::hexToRGBA("#F8F8FF")},
        {"gold", HtmlColor::hexToRGBA("#FFD700")},
        {"goldenrod", HtmlColor::hexToRGBA("#DAA520")},
        {"gray", HtmlColor::hexToRGBA("#808080")},
        {"green", HtmlColor::hexToRGBA("#008000")},
        {"greenyellow", HtmlColor::hexToRGBA("#ADFF2F")},
        {"honeydew", HtmlColor::hexToRGBA("#F0FFF0")},
        {"hotpink", HtmlColor::hexToRGBA("#FF69B4")},
        {"indianred", HtmlColor::hexToRGBA("#CD5C5C")},
        {"indigo", HtmlColor::hexToRGBA("#4B0082")},
        {"ivory", HtmlColor::hexToRGBA("#FFFFF0")},
        {"khaki", HtmlColor::hexToRGBA("#F0E68C")},
        {"lavender", HtmlColor::hexToRGBA("#E6E6FA")},
        {"lavenderblush", HtmlColor::hexToRGBA("#FFF0F5")},
        {"lawngreen", HtmlColor::hexToRGBA("#7CFC00")},
        {"lemonchiffon", HtmlColor::hexToRGBA("#FFFACD")},
        {"lightblue", HtmlColor::hexToRGBA("#ADD8E6")},
        {"lightcoral", HtmlColor::hexToRGBA("#F08080")},
        {"lightcyan", HtmlColor::hexToRGBA("#E0FFFF")},
        {"lightgoldenrodyellow", HtmlColor::hexToRGBA("#FAFAD2")},
        {"lightgray", HtmlColor::hexToRGBA("#D3D3D3")},
        {"lightgreen", HtmlColor::hexToRGBA("#90EE90")},
        {"lightpink", HtmlColor::hexToRGBA("#FFB6C1")},
        {"lightsalmon", HtmlColor::hexToRGBA("#FFA07A")},
        {"lightseagreen", HtmlColor::hexToRGBA("#20B2AA")},
        {"lightskyblue", HtmlColor::hexToRGBA("#87CEFA")},
        {"lightslategray", HtmlColor::hexToRGBA("#778899")},
        {"lightsteelblue", HtmlColor::hexToRGBA("#B0C4DE")},
        {"lightyellow", HtmlColor::hexToRGBA("#FFFFE0")},
        {"lime", HtmlColor::hexToRGBA("#00FF00")},
        {"limegreen", HtmlColor::hexToRGBA("#32CD32")},
        {"linen", HtmlColor::hexToRGBA("#FAF0E6")},
        {"magenta", HtmlColor::hexToRGBA("#FF00FF")},
        {"maroon", HtmlColor::hexToRGBA("#800000")},
        {"mediumaquamarine", HtmlColor::hexToRGBA("#66CDAA")},
        {"mediumblue", HtmlColor::hexToRGBA("#0000CD")},
        {"mediumorchid", HtmlColor::hexToRGBA("#BA55D3")},
        {"mediumpurple", HtmlColor::hexToRGBA("#9370DB")},
        {"mediumseagreen", HtmlColor::hexToRGBA("#3CB371")},
        {"mediumslateblue", HtmlColor::hexToRGBA("#7B68EE")},
        {"mediumspringgreen", HtmlColor::hexToRGBA("#00FA9A")},
        {"mediumturquoise", HtmlColor::hexToRGBA("#48D1CC")},
        {"mediumvioletred", HtmlColor::hexToRGBA("#C71585")},
        {"midnightblue", HtmlColor::hexToRGBA("#191970")},
        {"mintcream", HtmlColor::hexToRGBA("#F5FFFA")},
        {"mistyrose", HtmlColor::hexToRGBA("#FFE4E1")},
        {"moccasin", HtmlColor::hexToRGBA("#FFE4B5")},
        {"navajowhite", HtmlColor::hexToRGBA("#FFDEAD")},
        {"navy", HtmlColor::hexToRGBA("#000080")},
        {"oldlace", HtmlColor::hexToRGBA("#FDF5E6")},
        {"olive", HtmlColor::hexToRGBA("#808000")},
        {"olivedrab", HtmlColor::hexToRGBA("#6B8E23")},
        {"orange", HtmlColor::hexToRGBA("#FFA500")},
        {"orangered", HtmlColor::hexToRGBA("#FF4500")},
        {"orchid", HtmlColor::hexToRGBA("#DA70D6")},
        {"palegoldenrod", HtmlColor::hexToRGBA("#EEE8AA")},
        {"palegreen", HtmlColor::hexToRGBA("#98FB98")},
        {"paleturquoise", HtmlColor::hexToRGBA("#AFEEEE")},
        {"palevioletred", HtmlColor::hexToRGBA("#DB7093")},
        {"papayawhip", HtmlColor::hexToRGBA("#FFEFD5")},
        {"peachpuff", HtmlColor::hexToRGBA("#FFDAB9")},
        {"peru", HtmlColor::hexToRGBA("#CD853F")},
        {"pink", HtmlColor::hexToRGBA("#FFC0CB")},
        {"plum", HtmlColor::hexToRGBA("#DDA0DD")},
        {"powderblue", HtmlColor::hexToRGBA("#B0E0E6")},
        {"purple", HtmlColor::hexToRGBA("#800080")},
        {"rebeccapurple", HtmlColor::hexToRGBA("#663399")},
        {"red", HtmlColor::hexToRGBA("#FF0000")},
        {"rosybrown", HtmlColor::hexToRGBA("#BC8F8F")},
        {"royalblue", HtmlColor::hexToRGBA("#4169E1")},
        {"saddlebrown", HtmlColor::hexToRGBA("#8B4513")},
        {"salmon", HtmlColor::hexToRGBA("#FA8072")},
        {"sandybrown", HtmlColor::hexToRGBA("#F4A460")},
        {"seagreen", HtmlColor::hexToRGBA("#2E8B57")},
        {"seashell", HtmlColor::hexToRGBA("#FFF5EE")},
        {"sienna", HtmlColor::hexToRGBA("#A0522D")},
        {"silver", HtmlColor::hexToRGBA("#C0C0C0")},
        {"skyblue", HtmlColor::hexToRGBA("#87CEEB")},
        {"slateblue", HtmlColor::hexToRGBA("#6A5ACD")},
        {"slategray", HtmlColor::hexToRGBA("#708090")},
        {"snow", HtmlColor::hexToRGBA("#FFFAFA")},
        {"springgreen", HtmlColor::hexToRGBA("#00FF7F")},
        {"steelblue", HtmlColor::hexToRGBA("#4682B4")},
        {"tan", HtmlColor::hexToRGBA("#D2B48C")},
        {"teal", HtmlColor::hexToRGBA("#008080")},
        {"thistle", HtmlColor::hexToRGBA("#D8BFD8")},
        {"tomato", HtmlColor::hexToRGBA("#FF6347")},
        {"turquoise", HtmlColor::hexToRGBA("#40E0D0")},
        {"violet", HtmlColor::hexToRGBA("#EE82EE")},
        {"wheat", HtmlColor::hexToRGBA("#F5DEB3")},
        {"white", HtmlColor::hexToRGBA("#FFFFFF")},
        {"whitesmoke", HtmlColor::hexToRGBA("#F5F5F5")},
        {"yellow", HtmlColor::hexToRGBA("#FFFF00")},
        {"yellowgreen", HtmlColor::hexToRGBA("#9ACD32")}
    };


public:
    static RGBA getColor(const std::string& name) {
        auto it = colorMap.find(name);
        if (it != colorMap.end()) {
            return it->second;
        }
        return colorMap["black"]; // fallback
    }

    static Uint32 getColorUint32(const std::string& name, SDL_Surface* surface) {
        auto it = colorMap.find(name);
        if (it != colorMap.end()) {
            return Primitives::rgbToUint32(surface, it->second.r, it->second.g, it->second.b);
        }
        return Primitives::rgbToUint32(surface, colorMap["black"].r, colorMap["black"].g, colorMap["black"].b);
    }

};


#endif // HTML_COLOR_H
