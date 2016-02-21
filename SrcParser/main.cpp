//
//  main.cpp
//  SrcParser
//
//  Created by Evgeniy Shumakov on 21.02.16.
//  Copyright © 2016 Evgeniy Shumakov. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <stdio.h>
#include <dirent.h>


int SourceFilesCount;
int HeaderFilesCount;
int FoldersCount;

using namespace std;

enum arg_type {
    source,
    header,
    folder,
    none
};



void srcparser(string arg, arg_type mode) {
    
    int count;
    string line;
    
    
    
    switch (mode) {
        case source: case header:
            try {
                ifstream ifile(arg);
                if(ifile.is_open()) {
                    cout << "Filename:\t" << arg << "\n";
                    cout << "Included:\n";
                    while(getline(ifile,line)) {
                        if(line.substr(0,8)=="#include") {
                            cout << "\t" << line.substr(9,line.length()-9) << "\n";
                            count++;
                        }
                    }
                    if(count>0) {
                        cout << "Founds:" << count << "\n";
                        count=0;
                    }
                    else {
                        cout << "No include founds\n";
                    }
                    ifile.close();
                    break;
                }
            }
            catch (exception e) {
                cout << e.what() << "\n";
            }
     
        case folder: {
            
            string pwd = arg;
            map<string,arg_type> files;
            try {
                /* Change dir into folder path
                /  foreach files in path call recurse srcparser(filename,mode) function
                /  mode = source or header
                /  switch type of file SourceFilesCount or HeaderFilesCount
                /  will be incremented
                /  Foreach subfolder in path call recurse srcparser(path,mode) function
                /  mode = folder
                */
                
                DIR *dfd;
                struct dirent *dp;
              
                if ( !(dfd=opendir(arg.c_str()) ))
                    exit(1);
                
                while( (dp=readdir(dfd)) != NULL ) {
                    if(dp->d_type==DT_REG) {
                            files.insert(pair<string,arg_type>(dp->d_name,header));
                            cout << "Adding:" << dp->d_name << "\t" << "header\n";
                    }
                }
                    
                
                closedir(dfd);

                
                map<string,arg_type>::iterator it;
                for(it=files.begin();it!=files.end();it++) {
                    if(it->second==source) {
                        srcparser(it->first,it->second);
                        SourceFilesCount++;
                        
                    }
                    if(it->second==header) {
                        HeaderFilesCount++;
                        //srcparser(it->first,it->second);
                        
                    }
                    cout << "Element:" <<it->first << "\n";
                }
            }
            catch(exception e) {
                cout << e.what();
            }
        }
    }
    
    

    
        
}

void argparser(int argc, const char * argv[]) {
    
    arg_type mode=none;
    // Validation number of arguments
    
    if(argc<1) {
        cout << "Incorrect number of arguments\n";
        exit(0);
    }
    
    string path = argv[1];
    if(path.substr(path.length()-4,4)==".cpp") {
        mode=source;
        
    }
    if(path.substr(path.length()-2,2)==".h") {
        mode=header;
    }
    
    if(mode!=source && mode!=header) {
        mode = folder;
        srcparser(path,mode);
    }
    else
        srcparser(path,mode);
}

int main(int argc, const char * argv[]) {
    // Test block
    
    
    
  
    argparser(argc,argv);
    
    
    
    
    
    return 0;
}
