﻿/**
@brief    FBX用 ツール
@file     FBXDataTool.cpp
@author   Fumi.Iseki (C)
*/

#include  "FBXDataTool.h"


using namespace jbxl;


///////////////////////////////////////////////////////////////////////////////////////////////////
//

FBXData::~FBXData(void)
{
    DEBUG_MODE PRINT_MESG("FBXData::DESTRUCTOR:\n");
    this->free();
}


void  FBXData::init(int n)
{
    this->fbx_name    = init_Buffer();
    this->num_fbx     = n;
    this->phantom_out = true;
    this->no_offset   = false;

    this->forUnity    = true;
    this->forUE       = false;

    this->engine      = JBXL_3D_ENGINE_UE;
    this->next        = NULL;
    this->affineTrans = NULL;
    this->skeleton.init();
}


void  FBXData::free(void)
{
    free_Buffer(&(this->fbx_name));
    this->skeleton.free();
    this->delAffineTrans();
    this->affineTrans = NULL;

    this->delete_next();
}


void  FBXData::setEngine(int e)
{
    this->setUnity(false);
    this->setUE(false);
    //
    this->engine = e;
    if (e==JBXL_3D_ENGINE_UNITY)   this->setUnity(true);
    else if (e==JBXL_3D_ENGINE_UE) this->setUE(true);

    return;
}


void  FBXData::delete_next(void)
{
    if (this->next==NULL) return;

    FBXData* _next = this->next;
    while (_next!=NULL) {
        FBXData* _curr_node = _next;
        _next = _next->next;
        _curr_node->next = NULL;
        delete(_curr_node);
    }
    this->next = NULL;
}


void  FBXData::outputFile(const char* fname, const char* out_path, const char* tex_dirn)
{
    FILE* fp = NULL;
    char* packname = pack_head_tail_char(get_file_name(fname), ' ');
    Buffer file_name = make_Buffer_bystr(packname);
    ::free(packname);

    canonical_filename_Buffer(&file_name);
    if (file_name.buf[0]=='.') file_name.buf[0] = '_';
    //
    Buffer fbx_path;    // 出力パス
    if (out_path==NULL) fbx_path = make_Buffer_bystr("./");
    else                fbx_path = make_Buffer_bystr(out_path);
    //
    Buffer rel_tex;     //  Texture 相対パス
    if (tex_dirn==NULL) rel_tex = make_Buffer_bystr("");
    else                rel_tex = make_Buffer_bystr(tex_dirn);

    cat_Buffer(&file_name, &fbx_path);
    change_file_extension_Buffer(&fbx_path, ".fbx");

    fp = fopen((char*)fbx_path.buf, "wb");
    if (fp!=NULL) {
        this->output_fbx(fp);
        fclose(fp);
    }
    //
    free_Buffer(&fbx_path);
    free_Buffer(&rel_tex);
    //
    return;
}


//////////////////////////////////////////////////////////////////////////////////////////

void  FBXData::addObject(MeshObjectData* meshdata, bool collider, SkinJointData* joints)
{
    if (meshdata==NULL) return;

    if (collider) {
    }

    if (joints!=NULL) {
    }

    return;
}


/**
Vector<double>  FBXData::execAffineTrans(void)

FBXデータの Affine変換を行う．
no_offset が trueの場合，データの中心を原点に戻し，実際の位置をオフセットで返す．
*/
Vector<double>  FBXData::execAffineTrans(void)
{
    Vector<double> center(0.0, 0.0, 0.0);

    FBXData* fbx = this->next;  // Top はアンカー
    if (fbx!=NULL && this->no_offset) center = fbx->affineTrans->shift;

    return center;
}


void  FBXData::output_fbx(FILE* fp)
{
    if (fp==NULL) return;
    
    return;
}

