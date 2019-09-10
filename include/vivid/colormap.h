#pragma once

//  colormaps from [1], great job guys!

/*
    [1] https://github.com/BIDS/colormap

    mpl-colormaps by Nathaniel Smith & Stefan van der Walt

    To the extent possible under law, the persons who associated CC0 with
    mpl-colormaps have waived all copyright and related or neighboring rights
    to mpl-colormaps.

    You should have received a copy of the CC0 legalcode along with this
    work. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
*/

#include "vivid/types.h"
#include <vector>
#include <string>

namespace vivid {


class ColorMap
{
    public:

        enum class Preset {
            BlueYellow,
            CoolWarm,
            Hsl,
            HslPastel,
            Inferno,
            Magma,
            Plasma,
            Rainbow,
            Turbo,
            Viridis,
            Vivid
        };

        enum class Interpolation {
            Nearest,
            Linear,
            Hsv,
            Hsl,
            Lch
        };

        ColorMap() = default;
        ColorMap( const Preset type );
        ColorMap( const std::string& file );

        bool empty() const { return stops_.empty(); }
        size_t numStops() const { return stops_.size(); }
        srgb_t at( const float t ) const;
        const std::vector<srgb_t>& stops() const { return stops_; }

        Interpolation interpolation = Interpolation::Linear;

        static std::string nameForPreset( const Preset type );

    private:

        static std::vector<srgb_t> loadFromFile( const std::string& filename );
        std::vector<srgb_t> stops_;
};


}   //  ::vivid
