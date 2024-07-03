﻿#ifndef  __JBXL_CPP_FBX_TOOL_H_
#define  __JBXL_CPP_FBX_TOOL_H_

/**
  Wavefront FBX ファイル用ツール

*/

#include  "tools++.h"
#include  "txml.h"

#include  "TriBrep.h"
#include  "Rotation.h"
#include  "ContourBaseData.h"
#include  "MaterialParam.h"
#include  "MeshObjectData.h"


namespace jbxl {


//////////////////////////////////////////////////////////////////////////////////////////
//

/**
先頭のデータはアンカー．
アンカーでない場合は num_fbx == -1
*/
class  FBXData
{
public:
    FBXData(int n=0) { this->init(n);}  // n: FBXデータの総数．デフォルト（n=0）ではアンカーを作る
    virtual ~FBXData(void);

public:
    Buffer  fbx_name;
    bool    phantom_out;
    int     num_fbx;                    // nextに続くFBXデータの総数．
    bool    has_joints;
    bool    no_offset;

    bool    forUnity;
    bool    forUE;
    int     engine;

    AffineTrans<double>* affineTrans;
    AffineTrans<double>  skeleton;

    FBXData* next;

public:
    void    init(int n); 
    void    free(void); 
    void    delete_next(void);

    void    setUnity(bool b) { this->forUnity = b; this->forUE = !b;}
    void    setUE(bool b)    { this->forUE = b; this->forUnity = !b;}
    void    setEngine(int);

    void    setAffineTrans (AffineTrans<double> a) { delAffineTrans(); affineTrans = new AffineTrans<double>(); affineTrans->dup(a);}
    void    delAffineTrans (void) { freeAffineTrans(this->affineTrans);}
    Vector<double> execAffineTrans(void);

    void    addObject(MeshObjectData* meshdata, bool collider, SkinJointData* joints=NULL);
    void    closeSolid(void) {}

    void    outputFile(const char* fn, const char* out_path, const char* tex_dirn);
    void    output_fbx(FILE* fp);
};


inline void  freeFBXData(FBXData* fbx) { if(fbx!=NULL) { fbx->free(); delete fbx; fbx=NULL;} }


}

#endif
