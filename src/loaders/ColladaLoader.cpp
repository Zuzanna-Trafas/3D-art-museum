//
// Created by ztrafas on 27.08.2020.
//

#include "ColladaLoader.h"
using namespace rapidxml;

AnimatedModelData loadColladaModel(std::string colladaFile, int maxWeights) {
    file<> xmlFile(colladaFile); // Default template is char
    xml_document<> doc;
    doc.parse<0>(xmlFile.data());
    /*
    colladaFile <> document; // domyślnym typem jest char
    try {
        document.parse < 0 >( text ); // 0 to domyślny tryb parsowania
    }
    catch( const parse_error & e ) {
        std::cerr << e.what() << " here: " << e.where < char >() << std::endl;
        return - 1;
    }
    */
}
