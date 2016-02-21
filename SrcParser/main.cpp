//
//  main.cpp
//  SrcParser
//
//  Created by Evgeniy Shumakov on 21.02.16.
//  Copyright © 2016 Evgeniy Shumakov. All rights reserved.
//

#include <iostream>

void argparser(int argc, const char * argv[]) {
    
    // Validation number of arguments
    
    if(argc<1) {
        std::cout << "Incorrect number of arguments\n";
        exit(0);
    }
    
    
}

void srcparser(char * argv[]) {
    // Cheking if single source file in argument
    if(argv[0]=="source.cpp") {
        std::cout << "Source file specified\n";
    }
    else {
        std::cout << "Directory specified\n";
    }
    
        
}

int main(int argc, const char * argv[]) {
    
    argparser(argc,argv);
    
    return 0;
}
