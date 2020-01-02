#include "../../../config.h"
#ifdef TREES
#include "TreeSeed.h"
//Copyright (c) 2016 Kornelius Heru Cakra Murti
//MIT licence inside -> TerrainFactory/ProceduralTrees/kornJungle
namespace irr
{
    namespace scene
    {
        namespace jungleScene
        {

            TreeSeed::TreeSeed()
            {
                //ctor
                active = false;
                time = -1;
                age = 0;
            }

            TreeSeed::~TreeSeed()
            {
                //dtor
            }
        }
    }
}
#endif
