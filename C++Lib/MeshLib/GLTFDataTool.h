﻿#ifndef  __JBXL_CPP_GLTF_TOOL_H_
#define  __JBXL_CPP_GLTF_TOOL_H_

/**
  Wavefront GLTF ファイル用ツール

*/

#include  "tools++.h"
#include  "txml.h"
#include  "tjson.h"

#include  "TriBrep.h"
#include  "Rotation.h"
#include  "ContourBaseData.h"
#include  "MaterialParam.h"
#include  "MeshObjectData.h"


namespace jbxl {


#define  GLTF_STR_COPYRIGHT    "from OpenSimulator"
#define  GLTF_STR_GENERATOR    "JBXL glTF Tool Library (C) 2024 v1.0 by Fumi.Iseki"
#define  GLTF_STR_VERSION      "2.0"


//////////////////////////////////////////////////////////////////////////////////////////
//

/**
先頭のデータはアンカー．
アンカーでない場合は num_gltf == -1
*/
class  GLTFData
{
public:
    GLTFData(int n=0) { this->init(n);}  // n: GLTFデータの総数．デフォルト（n=0）ではアンカーを作る
    virtual ~GLTFData(void);

public:
    Buffer  gltf_name;
    bool    phantom_out;
    int     num_gltf;                    // nextに続くGLTFデータの総数．
    bool    has_joints;
    bool    no_offset;

    bool    forUnity;
    bool    forUE;
    int     engine;

    AffineTrans<double>* affineTrans;
    AffineTrans<double>  skeleton;

    GLTFData* next;

    tJson*  json_data;

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

    void    initGLTF(void);

    void    addObject(MeshObjectData* meshdata, bool collider, SkinJointData* joints=NULL);
    void    closeSolid(void) {}

    void    outputFile(const char* fn, const char* out_path, const char* tex_dirn);
    void    output_gltf(FILE* fp);
};


inline void  freeGLTFData(GLTFData* gltf) { if(gltf!=NULL) { gltf->free(); delete gltf; gltf=NULL;} }


}

#endif
