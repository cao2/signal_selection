//
//  read_spec.cpp
//  
//
//  Created by Yuting Cao on 5/28/17.
//
//
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include "fuc.h"
#include "msg_def.h"
struct prot{
    string prot_name;
    vector<message_t> msgs;
};
void prot_string(prot x){
    cout<<x.prot_name<<":"<<endl;
    uint16_t i=0;
    for(;i<x.msgs.size();i++)
        cout<<x.msgs.at(i).toString()<<endl;
}


struct chan{
    string chan_name;
    uint32_t src;
    uint32_t dest;
    vector<command_t> cmds;
};

float calculateSD(vector<float> data)
{
    float sum = 0.0, mean, standardDeviation = 0.0;
    
    int i;
    
    for(i = 0; i < data.size(); ++i)
    {
        sum += data.at(i);
    }
    //cout<< "sum "<<sum<<endl;
    mean = sum/data.size();
    //cout<<"mean:"<<mean<<endl;
    for(i = 0; i < data.size(); ++i)
        standardDeviation += pow(data[i] - mean, 2);
    //cout<<"now "<<standardDeviation<<endl;
    return sqrt(standardDeviation / data.size());
}

void chan_string(chan x){
    cout<<x.chan_name<<" "<<blk_vector[x.src]<<" "<<blk_vector[x.dest]<<"  cmd::";
    
    uint16_t i=0;
    for(;i<x.cmds.size();i++)
        cout<<cmd_vector[x.cmds.at(i)]<<" ";
    cout<<endl;
}
vector<prot> parse_spec(string filename){
    vector<prot> specs;
        ifstream lpn_file(filename);
        string line;
        if (lpn_file.is_open()){
            while(getline(lpn_file,line)){
                if ( !line.empty()&&line.at(0)=='*'){
                    prot new_prot;
                    new_prot.prot_name= line;
                    //cout<<line<<endl;
                while(getline(lpn_file,line)&& !line.empty()){
                    message_t msg;
                    std::istringstream iss;
                    iss.str(line);
                    string srt,dest,cmd,sequence,condition;
                    iss>>srt;
                    iss>>dest;
                    iss>>cmd;
                    iss>>sequence;
                    iss>>condition;
                    msg.src=msg.get_src(srt);
                    msg.dest=msg.get_src(dest);
                    msg.cmd=msg.get_cmd(cmd);
                    //cout<<msg.toString()<<endl;
                    new_prot.msgs.push_back(msg);
            }
                    specs.push_back(new_prot);
            }
        }
        }
        else{
            cout<<"ERROR lpn file "<<filename<<" can't be opened"<<endl;
        }
        return specs;
    }


vector<chan> parse_channel(string filename){
    vector<chan> chanls;
    ifstream lpn_file(filename);
    string line;
    if (lpn_file.is_open()){
        while(getline(lpn_file,line)){
            if ( !line.empty()&&line.at(0)=='*'){
                chan new_chan;
                message_t msg;
                new_chan.chan_name= line;
                //
                //cout<<line<<endl;
                getline(lpn_file, line);
                new_chan.src=msg.get_src(line);
                getline(lpn_file, line);
                new_chan.dest=msg.get_src(line);
                getline(lpn_file,line);
                std::istringstream iss;
                iss.str(line);
                string tmp_cmd;
                while(iss>>tmp_cmd){
                    new_chan.cmds.push_back(msg.get_cmd(tmp_cmd));
                    //cout<<"push back commands "<<msg.get_cmd(tmp_cmd)<<endl;
                }
                
                chanls.push_back(new_chan);
            }
        }
    }
    else{
        cout<<"ERROR lpn file "<<filename<<" can't be opened"<<endl;
    }
    return chanls;
}



