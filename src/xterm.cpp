#include "vivid/conversion.h"
#include "vivid/colortable.h"

namespace tq::xterm {


////////////////////////////////////////////////////////////////////////////////
std::string fromRGB( const col_t& rgb ) {
    return xterm::fromIndex( index::fromRGB( rgb ) );
}


////////////////////////////////////////////////////////////////////////////////
std::string fromIndex( const uint8_t index ) {
    return ColorTable::name( index );
}


}   //  ::tq::xterm
