//
//  sig_selec.cpp/Users/cao2/Desktop/signal_selection
//  
//
//  Created by Yuting Cao on 1/22/18.
//
#include <map>
#include <set>
#include <stdio.h>
#include <algorithm>
#include <functional>
#include "read_spec.h"
int main(int argc, char *argv[]){
    //cout<<"reading specification file "<<argv[1]<<endl;
    vector<prot> specs=parse_spec(argv[1]);
    vector<chan> chanls=parse_channel(argv[2]);
    uint16_t i;
    //for (i=0;i<chanls.size();i++)
    //    chan_string(chanls.at(i));
    cout<<"There are "<<chanls.size()<<" channels processed"<<endl;
    cout<<specs.size()<<" specifications"<<endl;
    
    
    
    
    
    
    
    
    //now for each channel
    //for (i=0;i<1;i++){
    set<pair<double, int> > dis_map;
    for (i=0;i<chanls.size();i++){
        cout<<endl<<endl<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
        cout<<"processing channel "<<i<<"::::::::";
        vector< vector<uint16_t> > groups;
        chan tmp_chan=chanls.at(i);
        chan_string(tmp_chan);
        
        
        
        uint16_t j=0;
        for(j=0;j<tmp_chan.cmds.size();j++)
        {
            vector<uint16_t> tmp_v;
            groups.push_back(tmp_v);
        }
        vector<uint16_t> tmp_v;
        groups.push_back(tmp_v);
        
        //check through each specification.. see if this is covered
        
        for (j=0;j<specs.size();j++){
            bool find=false;
            prot tmp_prot=specs.at(j);
            uint16_t x=0;
            for(x=0 ; x<tmp_prot.msgs.size();x++){
                if (tmp_prot.msgs.at(x).src==tmp_chan.src && tmp_prot.msgs.at(x).dest==tmp_chan.dest){
                    uint16_t y=0;
                    for (y=0;y<tmp_chan.cmds.size();y++){
                        if (tmp_prot.msgs.at(x).cmd==tmp_chan.cmds.at(y) && find==false){
                            //cout<<"find matching message in "<<tmp_prot.prot_name<<":::::::::::";
                            //cout<<tmp_prot.msgs.at(x).toString()<<endl;
                            groups.at(y).push_back(j);
                            find=true;
                        }
                    }
                }
            }
            if (find==false){
                groups.at(tmp_chan.cmds.size()).push_back(j);
                //cout<<"not cotained in "<<tmp_prot.prot_name<<endl;
            }
                
        }
        
        cout<<"totoal number of group: "<<groups.size()<<endl;
        vector< float> group_size;
        for(j=0;j<tmp_chan.cmds.size();j++){
            cout<<"group "<<j<<", cmd is "<<cmd_vector[tmp_chan.cmds.at(j)]<<", total numbers of speci "<<groups.at(j).size()<<endl;
            if (groups.at(j).size()>0)
                group_size.push_back(groups.at(j).size());
        }
        cout<<"group "<<j<<", cmd is none, total numbers of speci "<<groups.at(j).size()<<endl;
        if (groups.at(j).size()>0)
            group_size.push_back(groups.at(j).size());
        
        cout<<"group size "<<group_size.size()<<endl;
        cout<<"standard deviation "<<calculateSD(group_size)<<endl;
        cout<<"distinguishing power is size/(1+sd) "<<(group_size.size()*1.0)/(1+calculateSD(group_size))<<endl;
        double dis=(group_size.size()*1.0)/(1+calculateSD(group_size));
        //cout<<"size of dis_map "<<dis_map.size()<<endl;
        dis_map.insert(pair<double, int>(dis,i));
    }
    
    cout<<"size of dis_map "<<dis_map.size()<<endl;
   
    for (pair<float, int> element : dis_map)
    {
        int ind=element.second;
        cout << element.first << " :: channel " << ind<< ":";
        chan_string(chanls.at(ind));
    }
    return 0;
}
