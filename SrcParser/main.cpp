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

    

using namespace std;

int SourceFilesCount;
int HeaderFilesCount;
int FoldersCount;



enum arg_type {
    source,
    header,
    folder,
    none
};

void show_resut(string filename, int single_comments, int include_counts,int code_lines, int lines,map<int,string> includes) {
    map<int,string>::iterator it2;
    cout << "Filename:"<<filename<<"\n";
    for(it2=includes.begin();it2!=includes.end(); it2++) {
        cout << "\t|_" << it2->second << "\n";
    }
    
    cout << "----------------------------"<<"\n";
    cout << "| Includes:"<<include_counts<<"\n";
    cout << "| Comments:"<<single_comments<<"\n";
    cout << "| Code lines:"<<code_lines<<"\n";
    cout << "| Sumary lines:"<<lines<<"\n";
    cout << "----------------------------"<<"\n";
    
}

void srcparser(string arg, arg_type mode) {
    
    int include_counts;
    int single_comments;
    int lines;
    int code_lines;
    string line;
    map<int,string> includes;
    
    
    switch (mode) {
        case source: case header:
            
            try {
                ifstream ifile(arg);
                
                if(ifile.is_open()) {
                    
                    
                    while(getline(ifile,line)) {
                        lines++;
                        code_lines++;
                        if(line.substr(0,8)=="#include") {
                            includes.insert(pair<int,string>(0,line.substr(9,line.length()-9)));
                            cout << "Added:"<<line.substr(9,line.length()-9)<<"\n";
                            include_counts++;
                            
                            
                        }
                        
                        if ((line.find("//")!=string::npos)) {
                            single_comments++;
                            code_lines--;
                        }
                       
                    }
                    
                    ifile.close();
                    
                    if((include_counts>0)||(single_comments>0)||(lines>0)) {
                        show_resut(arg,single_comments,include_counts,code_lines,lines, includes);
                    }
                    else {
                        cout << "No records in file\n";
                    }
                    
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

