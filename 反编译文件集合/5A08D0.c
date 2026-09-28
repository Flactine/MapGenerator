// sub_5A08D0 @ 0x5A08D0 (full body, IDA MCP)

char __fastcall sub_5A08D0(_DWORD *n8_1, int a2, int a3, float a4, int *a5, __int16 *a6, char a7)
{
  int v8; // eax
  int n100; // esi
  void *n8_8; // eax
  _DWORD *v11; // esi
  int n100_1; // eax
  void *v13; // eax
  int v14; // ecx
  int v15; // eax
  int *v16; // ebx
  CellClass *i; // eax
  _DWORD *v18; // eax
  int pMapCoord__3; // ecx
  float *n8_3; // edi
  int v21; // edx
  int v22; // ecx
  int v23; // eax
  int v24; // edx
  _DWORD *n8_2; // ebx
  int v26; // ecx
  double v27; // st7
  double v28; // st7
  char v30; // c0
  float *n8_5; // eax
  unsigned int v32; // ecx
  unsigned int v33; // edx
  int v34; // edi
  int v35; // ebx
  unsigned int n8_6; // ecx
  long double v37; // st7
  unsigned int v38; // eax
  CellStruct *pMapCoord; // ecx
  int v40; // eax
  CellStruct *pMapCoord_4; // edi
  char *v42; // edi
  CellClass *CellAt_MapCrd; // eax
  char v44; // al
  int v45; // eax
  _DWORD *v46; // edi
  char *v47; // eax
  int v48; // ecx
  CellClass *v49; // eax
  CellStruct *v50; // ebx
  __int16 pMapCoord__1; // ax
  int v52; // edi
  int v53; // ecx
  double v54; // st7
  double v55; // st7
  char v57; // c0
  int v58; // eax
  int pMapCoord__2; // edx
  CellStruct *v60; // eax
  unsigned int v61; // ecx
  unsigned int v62; // edi
  unsigned int v63; // edx
  int v64; // edi
  int v65; // ebx
  unsigned int v66; // ecx
  int v67; // eax
  double v68; // st7
  CellStruct *pMapCoord_2; // ecx
  bool v70; // zf
  int v71; // eax
  CellStruct *pMapCoord_3; // edi
  int v73; // eax
  __int16 *v74; // edi
  __int16 *v75; // ecx
  int v76; // eax
  int v77; // ecx
  _DWORD *v78; // eax
  int v79; // eax
  __int16 *v80; // edi
  char pFoundationData_3; // [esp+1Bh] [ebp-4Dh]
  CellStruct *v83; // [esp+1Ch] [ebp-4Ch]
  CellStruct *pMapCoord_1; // [esp+1Ch] [ebp-4Ch]
  int pMapCoord_; // [esp+20h] [ebp-48h] BYREF
  _DWORD *v86; // [esp+24h] [ebp-44h]
  void *n8_7; // [esp+28h] [ebp-40h]
  void *pMapCoord__4; // [esp+2Ch] [ebp-3Ch]
  void *n8_4; // [esp+30h] [ebp-38h]
  CellStruct *v90; // [esp+34h] [ebp-34h]
  int n8; // [esp+38h] [ebp-30h]
  double v92; // [esp+3Ch] [ebp-2Ch]
  float v93; // [esp+44h] [ebp-24h]
  _BYTE pMapCrd[28]; // [esp+48h] [ebp-20h] BYREF

  v8 = n8_1[96]; /*0x5a08de*/
  n8 = n8_1; /*0x5a08e4*/
  n100 = 2 * n8_1[97] * v8; /*0x5a08f4*/
  if ( n100 <= 100 ) /*0x5a08f6*/
    n100 = 100; /*0x5a08f8*/
  n8_8 = operator new(8 * n100); /*0x5a0905*/
  if ( n8_8 ) /*0x5a0911*/
  {
    n8_4 = n8_8; /*0x5a0914*/
    *pMapCrd = n100 - 1; /*0x5a0918*/
  }
  else
  {
    n8_4 = 0; /*0x5a091e*/
  }
  v11 = operator new(0x14u); /*0x5a0929*/
  if ( v11 ) /*0x5a0930*/
  {
    n100_1 = 2 * n8_1[97] * n8_1[96]; /*0x5a093f*/
    if ( n100_1 <= 100 ) /*0x5a0944*/
      n100_1 = 100; /*0x5a0946*/
    v11[3] = 0; /*0x5a0952*/
    v11[4] = -1; /*0x5a0956*/
    *v11 = 0; /*0x5a095d*/
    v11[1] = n100_1; /*0x5a095f*/
    v13 = operator new(4 * n100_1 + 4); /*0x5a0962*/
    v14 = v11[1]; /*0x5a0967*/
    v11[2] = v13; /*0x5a096a*/
    v15 = 0; /*0x5a0970*/
    if ( v14 >= 0 ) /*0x5a0974*/
    {
      do /*0x5a0983*/
      {
        ++v15; /*0x5a0979*/
        *(v11[2] + 4 * v15 - 4) = 0; /*0x5a097a*/
      }
      while ( v15 <= v11[1] ); /*0x5a0983*/
    }
  }
  else
  {
    v11 = 0; /*0x5a0987*/
  }
  v16 = a5; /*0x5a0989*/
  n8_7 = 0; /*0x5a098c*/
  HIBYTE(v83) = 1; /*0x5a0990*/
  *&pMapCrd[16] = 0; /*0x5a0995*/
  if ( *a5 ) /*0x5a099d*/
  {
    *&pMapCrd[16] = 0; /*0x5a09b0*/
  }
  else if ( a5[2] != 512 ) /*0x5a09c5*/
  {
    *&pMapCrd[16] = 0x400921FB54442D18LL; /*0x5a09c7*/
  }
  if ( a5[1] ) /*0x5a09d7*/
  {
    *&pMapCrd[16] = 0x4012D97C7F3321D2LL; /*0x5a09dc*/
  }
  else if ( a5[3] != 512 ) /*0x5a09f1*/
  {
    *&pMapCrd[16] = 0x3FF921FB54442D18LL; /*0x5a09f3*/
  }
  sub_578350(&MouseClass::Instance); /*0x5a0a08*/
  for ( i = MapClass::CellIteratorNext(&MouseClass::Instance); i; i = MapClass::CellIteratorNext(&MouseClass::Instance) ) /*0x5a0a19*/
  {
    LODWORD(v92) = i->MapCoords; /*0x5a0a1e*/
    *(dword_ABED10 + 20 * SLOWORD(v92) + 20 * dword_89C2DC * SWORD1(v92) + 15) = 0; /*0x5a0a43*/
  }
  v18 = sub_5A0700(n8, a3); /*0x5a0a58*/
  pMapCoord__3 = v18[4]; /*0x5a0a5d*/
  v86 = v18; /*0x5a0a60*/
  pMapCoord_ = pMapCoord__3; /*0x5a0a66*/
  pMapCoord__4 = 0; /*0x5a0a6a*/
  if ( pMapCoord__3 > 0 ) /*0x5a0a6e*/
  {
    n8_3 = n8_4; /*0x5a0a74*/
    while ( 1 ) /*0x5a0a83*/
    {
      v21 = *v16; /*0x5a0a83*/
      v90 = *(v86[1] + 4 * pMapCoord__4); /*0x5a0a88*/
      v22 = SHIWORD(v90); /*0x5a0a8c*/
      v23 = v90; /*0x5a0a91*/
      if ( v90 >= v21 ) /*0x5a0a96*/
      {
        if ( v90 >= v21 + v16[2] ) /*0x5a0aa3*/
          goto LABEL_48; /*0x5a0aa3*/
        v16 = a5; /*0x5a0aa9*/
        v24 = a5[1]; /*0x5a0aac*/
        if ( SHIWORD(v90) >= v24 ) /*0x5a0ab1*/
          break; /*0x5a0ab1*/
      }
LABEL_49:
      pMapCoord__4 = pMapCoord__4 + 1; /*0x5a0c19*/
      if ( pMapCoord__4 >= pMapCoord_ ) /*0x5a0c28*/
      {
        v18 = v86; /*0x5a0c2e*/
        goto LABEL_51; /*0x5a0c2e*/
      }
    }
    if ( SHIWORD(v90) < v24 + a5[3] ) /*0x5a0abe*/
    {
      *n8_3 = v90; /*0x5a0ac8*/
      n8_2 = (v23 - *a6); /*0x5a0ad2*/
      v26 = v22 - a6[1]; /*0x5a0ad8*/
      n8 = n8_2; /*0x5a0ada*/
      LODWORD(v92) = v26; /*0x5a0ae0*/
      if ( n8_2 ) /*0x5a0ae4*/
      {
        v27 = -(SLODWORD(v92) / n8); /*0x5a0af5*/
        sub_4CADE0(v27); /*0x5a0afa*/
        if ( n8_2 < 0 ) /*0x5a0b04*/
          v27 = 3.141592653589793 - SLODWORD(v92) / n8; /*0x5a0b06*/
      }
      else
      {
        v27 = 1.570796326794897; /*0x5a0be9*/
      }
      v28 = fabs(v27 - *&pMapCrd[16]); /*0x5a0b10*/
      *&pMapCrd[8] = v28; /*0x5a0b18*/
      if ( !v30 ) /*0x5a0b21*/
      {
        do /*0x5a0b34*/
          v28 = v28 - 6.283185307179586; /*0x5a0b23*/
        while ( v28 >= 6.283185307179586 ); /*0x5a0b34*/
        *&pMapCrd[8] = v28; /*0x5a0b36*/
      }
      if ( v28 > 3.141592653589793 ) /*0x5a0b45*/
        *&pMapCrd[8] = 6.283185307179586 - v28; /*0x5a0b4f*/
      *pMapCrd = Randomizer::Random(&dword_ABE890); /*0x5a0b5f*/
      n8_5 = n8_3; /*0x5a0b73*/
      n8_3 += 2; /*0x5a0b76*/
      n8_7 = n8_7 + 1; /*0x5a0b91*/
      LODWORD(v92) = n8_5; /*0x5a0b95*/
      n8 = n8_3; /*0x5a0b99*/
      *(n8_3 - 1) = *&pMapCrd[8] * 1.5 + *pMapCrd * 2.328306437080797e-10 * 2.0; /*0x5a0b9f*/
      v32 = *v11 + 1; /*0x5a0ba7*/
      *(&v92 + 1) = n8_5[1]; /*0x5a0ba8*/
      v33 = v32 >> 1; /*0x5a0bb1*/
      if ( v32 < v11[1] ) /*0x5a0bb5*/
      {
        if ( v32 <= 1 ) /*0x5a0bba*/
        {
          v16 = a5; /*0x5a0bf4*/
        }
        else
        {
          do /*0x5a0bda*/
          {
            v34 = v11[2]; /*0x5a0bbc*/
            v35 = *(v34 + 4 * v33); /*0x5a0bbf*/
            if ( *(v35 + 4) <= *(&v92 + 1) ) /*0x5a0bce*/
              break; /*0x5a0bce*/
            *(v34 + 4 * v32) = v35; /*0x5a0bd0*/
            v32 = v33; /*0x5a0bd3*/
            v33 >>= 1; /*0x5a0bd5*/
          }
          while ( v32 > 1 ); /*0x5a0bda*/
          v16 = a5; /*0x5a0bdc*/
          n8_5 = LODWORD(v92); /*0x5a0bdf*/
          n8_3 = n8; /*0x5a0be3*/
        }
        *(v11[2] + 4 * v32) = n8_5; /*0x5a0bfa*/
        n8_6 = v11[3]; /*0x5a0bff*/
        ++*v11; /*0x5a0c05*/
        if ( n8_5 > n8_6 ) /*0x5a0c07*/
          v11[3] = n8_5; /*0x5a0c09*/
        if ( n8_5 < v11[4] ) /*0x5a0c0f*/
          v11[4] = n8_5; /*0x5a0c11*/
        goto LABEL_49; /*0x5a0c14*/
      }
    }
LABEL_48:
    v16 = a5; /*0x5a0c16*/
    goto LABEL_49; /*0x5a0c16*/
  }
LABEL_51:
  if ( v18 ) /*0x5a0c36*/
    (**v18)(v18, 1); /*0x5a0c3e*/
  v37 = __FYL2X__(v83, 0.6931471805599453094); /*0x5a0c46*/
  if ( v37 < 1.0 ) /*0x5a0c55*/
    v37 = 1.0; /*0x5a0c59*/
  n8_7 = Game::F2I64(1.0 / (1.0 / v37 * a4) * 0.5); /*0x5a0c79*/
  *&pMapCrd[20] = (n8_7 / 2 + 1); /*0x5a0c95*/
  do /*0x5a0cc0*/
  {
    *&pMapCrd[4] = Randomizer::Random(&dword_ABE890); /*0x5a0ca3*/
    v38 = Game::F2I64(*&pMapCrd[4] * *&pMapCrd[20] * 2.328306437080797e-10); /*0x5a0cb9*/
  }
  while ( v38 > n8_7 / 2 ); /*0x5a0cc0*/
  n8_7 = n8_7 + v38; /*0x5a0cc8*/
  if ( *v11 ) /*0x5a0ccc*/
  {
    v40 = v11[2]; /*0x5a0cda*/
    pMapCoord_4 = *(v40 + 4); /*0x5a0ce2*/
    *(v40 + 4) = *(v40 + 4 * *v11); /*0x5a0ce5*/
    *(v11[2] + 4 * (*v11)--) = 0; /*0x5a0ced*/
    sub_5AD870(1); /*0x5a0cf7*/
    pMapCoord_1 = pMapCoord_4; /*0x5a0cfc*/
    pMapCoord = pMapCoord_4; /*0x5a0d00*/
  }
  else
  {
    pMapCoord = 0; /*0x5a0cd2*/
    pMapCoord_1 = 0; /*0x5a0cd4*/
  }
  n8_4 = 0; /*0x5a0d06*/
  if ( n8_7 <= 0 ) /*0x5a0d0c*/
    goto LABEL_113; /*0x5a0d0c*/
  while ( pFoundationData_3 && pMapCoord ) /*0x5a0d26*/
  {
    v42 = dword_ABED10 + 80 * pMapCoord->X + 80 * dword_89C2DC * pMapCoord->Y; /*0x5a0d48*/
    if ( !*(v42 + 14) ) /*0x5a0d4a*/
    {
      CellAt_MapCrd = MapClass::GetCellAt_MapCrd(&MouseClass::Instance, pMapCoord); /*0x5a0d57*/
      if ( sub_486380(CellAt_MapCrd) ) /*0x5a0d5e*/
      {
        v42[75] = 1; /*0x5a0d6a*/
        *(v42 + 14) = a3; /*0x5a0d6e*/
      }
      pMapCoord = pMapCoord_1; /*0x5a0d71*/
    }
    v44 = 0; /*0x5a0d7d*/
    n8 = 0; /*0x5a0d82*/
    v90 = (pMapCoord__4 + 8 * v86); /*0x5a0d86*/
    while ( 1 ) /*0x5a0df4*/
    {
      LODWORD(v92) = *CellStruct::GetFoundationMapCrd(pMapCoord, &pMapCrd[4], (4 * (v44 & 7) + 9041544)); /*0x5a0dad*/
      pMapCoord_ = LODWORD(v92); /*0x5a0db1*/
      v45 = SWORD1(v92) + SLOWORD(v92); /*0x5a0dbd*/
      if ( v45 <= dword_ABED04 /*0x5a0de6*/
        || SLOWORD(v92) - SWORD1(v92) >= dword_ABED04
        || SWORD1(v92) - SLOWORD(v92) >= dword_ABED04
        || v45 > dword_ABED08 )
      {
        goto LABEL_108; /*0x5a0de6*/
      }
      v46 = dword_ABED10; /*0x5a0dec*/
      if ( !dword_ABED10 ) /*0x5a0df4*/
        goto LABEL_105; /*0x5a0df4*/
      v47 = dword_ABED10 + 80 * SLOWORD(v92) + 80 * dword_89C2DC * SWORD1(v92); /*0x5a0e0b*/
      if ( !*(v47 + 14) && *(v47 + 15) != a3 && SLOWORD(v92) >= *a5 ) /*0x5a0e2d*/
      {
        if ( SLOWORD(v92) < *a5 + a5[2] ) /*0x5a0e3a*/
        {
          v48 = a5[1]; /*0x5a0e40*/
          if ( SWORD1(v92) >= v48 && SWORD1(v92) < v48 + a5[3] ) /*0x5a0e52*/
          {
            v49 = MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord_); /*0x5a0e62*/
            if ( sub_486380(v49) ) /*0x5a0e69*/
            {
              v50 = v90; /*0x5a0e76*/
              pMapCoord__1 = pMapCoord_; /*0x5a0e7a*/
              *v90 = pMapCoord_; /*0x5a0e81*/
              v53 = SHIWORD(pMapCoord_) - a6[1]; /*0x5a0e94*/
              v90 = (pMapCoord__1 - *a6); /*0x5a0e98*/
              v52 = v90; /*0x5a0e92*/
              LODWORD(v92) = v53; /*0x5a0e9c*/
              if ( v90 ) /*0x5a0ea0*/
              {
                v54 = -(SLODWORD(v92) / v90); /*0x5a0eb1*/
                sub_4CADE0(v54); /*0x5a0eb6*/
                if ( v52 < 0 ) /*0x5a0ec0*/
                  v54 = v54 + 3.141592653589793; /*0x5a0ec2*/
              }
              else
              {
                v54 = 1.570796326794897; /*0x5a0fe5*/
              }
              v55 = fabs(v54 - *&pMapCrd[12]); /*0x5a0ecc*/
              v92 = v55; /*0x5a0ed4*/
              if ( !v57 ) /*0x5a0edd*/
              {
                do /*0x5a0ef0*/
                  v55 = v55 - 6.283185307179586; /*0x5a0edf*/
                while ( v55 >= 6.283185307179586 ); /*0x5a0ef0*/
                v92 = v55; /*0x5a0ef2*/
              }
              if ( v55 > 3.141592653589793 ) /*0x5a0f01*/
                v92 = 6.283185307179586 - v55; /*0x5a0f0b*/
              *&pMapCrd[20] = Randomizer::Random(&dword_ABE890); /*0x5a0f1b*/
              *&pMapCrd[24] = 0; /*0x5a0f1f*/
              v58 = SHIWORD(pMapCoord_); /*0x5a0f2b*/
              pMapCoord__2 = pMapCoord_; /*0x5a0f48*/
              *&v50[1] = v92 * 1.5 + *&pMapCrd[20] * 2.328306437080797e-10 * 2.0; /*0x5a0f4f*/
              *(dword_ABED10 + 20 * pMapCoord__2 + 20 * dword_89C2DC * v58 + 15) = a3; /*0x5a0f6a*/
              v60 = v50; /*0x5a0f73*/
              v86 = (v86 + 1); /*0x5a0f75*/
              v61 = *v11 + 1; /*0x5a0f81*/
              v93 = *&v50[1]; /*0x5a0f82*/
              v62 = v11[1]; /*0x5a0f86*/
              v63 = v61 >> 1; /*0x5a0f8b*/
              LODWORD(v92) = v50; /*0x5a0f8f*/
              v90 = v50 + 2; /*0x5a0f93*/
              if ( v61 < v62 ) /*0x5a0f97*/
              {
                if ( v61 > 1 ) /*0x5a0fa0*/
                {
                  do /*0x5a0fc0*/
                  {
                    v64 = v11[2]; /*0x5a0fa2*/
                    v65 = *(v64 + 4 * v63); /*0x5a0fa5*/
                    if ( *(v65 + 4) <= v93 ) /*0x5a0fb4*/
                      break; /*0x5a0fb4*/
                    *(v64 + 4 * v61) = v65; /*0x5a0fb6*/
                    v61 = v63; /*0x5a0fb9*/
                    v63 >>= 1; /*0x5a0fbb*/
                  }
                  while ( v61 > 1 ); /*0x5a0fc0*/
                  v60 = LODWORD(v92); /*0x5a0fc2*/
                }
                *(v11[2] + 4 * v61) = v60; /*0x5a0fc9*/
                v66 = v11[3]; /*0x5a0fce*/
                ++*v11; /*0x5a0fd4*/
                if ( v60 > v66 ) /*0x5a0fd6*/
                  v11[3] = v60; /*0x5a0fd8*/
                if ( v60 < v11[4] ) /*0x5a0fde*/
                  v11[4] = v60; /*0x5a0fe0*/
              }
              goto LABEL_108; /*0x5a0fe3*/
            }
          }
        }
        v46 = dword_ABED10; /*0x5a0ff0*/
      }
      if ( v46 ) /*0x5a0ff8*/
      {
        v67 = v46[20 * pMapCoord_ + 14 + 20 * dword_89C2DC * SHIWORD(pMapCoord_)]; /*0x5a1013*/
        if ( !v67 ) /*0x5a1019*/
          goto LABEL_108; /*0x5a1019*/
      }
      else
      {
LABEL_105:
        v67 = -1; /*0x5a101d*/
      }
      if ( v67 != a3 ) /*0x5a1023*/
        pFoundationData_3 = 0; /*0x5a1025*/
LABEL_108:
      v44 = n8 + 2; /*0x5a102e*/
      n8 += 2; /*0x5a1034*/
      if ( n8 >= 8 ) /*0x5a1038*/
        break; /*0x5a1038*/
      pMapCoord = pMapCoord_1; /*0x5a0d8c*/
    }
    n8_4 = n8_4 + 1; /*0x5a1043*/
    v68 = sub_5980C0(&byte_ABDFB8); /*0x5a104c*/
    pMapCoord_2 = *v11; /*0x5a1057*/
    v70 = *v11 == 0; /*0x5a1059*/
    *&pMapCrd[12] = v68 * 0.7853981633974483 + *&pMapCrd[12]; /*0x5a105f*/
    if ( v70 ) /*0x5a1063*/
    {
      pMapCoord_1 = pMapCoord_2; /*0x5a1065*/
    }
    else
    {
      v71 = v11[2]; /*0x5a106b*/
      pMapCoord_3 = *(v71 + 4); /*0x5a1073*/
      *(v71 + 4) = *(v71 + 4 * pMapCoord_2); /*0x5a1076*/
      *(v11[2] + 4 * (*v11)--) = 0; /*0x5a107e*/
      sub_5AD870(1); /*0x5a108c*/
      pMapCoord_1 = pMapCoord_3; /*0x5a1091*/
    }
    if ( n8_4 < n8_7 ) /*0x5a109f*/
    {
      pMapCoord = pMapCoord_1; /*0x5a0d14*/
      continue; /*0x5a0d14*/
    }
    break;
  }
LABEL_113:
  if ( a7 ) /*0x5a10aa*/
  {
    if ( *v11 ) /*0x5a10b0*/
    {
      v73 = v11[2]; /*0x5a10ba*/
      v74 = *(v73 + 4); /*0x5a10c2*/
      *(v73 + 4) = *(v73 + 4 * *v11); /*0x5a10c5*/
      *(v11[2] + 4 * (*v11)--) = 0; /*0x5a10cd*/
      sub_5AD870(1); /*0x5a10db*/
      v75 = v74; /*0x5a10e2*/
      if ( v74 ) /*0x5a10e4*/
      {
        while ( pFoundationData_3 ) /*0x5a10ef*/
        {
          if ( dword_ABED10 ) /*0x5a10f9*/
          {
            v76 = 80 * (*v75 + dword_89C2DC * v75[1]); /*0x5a110e*/
            v77 = *(dword_ABED10 + v76 + 56); /*0x5a1111*/
            v78 = dword_ABED10 + v76 + 56; /*0x5a1115*/
            if ( !v77 ) /*0x5a111b*/
            {
              *v78 = a3; /*0x5a111d*/
              goto LABEL_123; /*0x5a111f*/
            }
          }
          else
          {
            v77 = -1; /*0x5a1121*/
          }
          if ( v77 != a3 ) /*0x5a1126*/
            pFoundationData_3 = 0; /*0x5a1128*/
LABEL_123:
          if ( !*v11 ) /*0x5a112d*/
            break; /*0x5a112d*/
          v79 = v11[2]; /*0x5a1133*/
          v80 = *(v79 + 4); /*0x5a113b*/
          *(v79 + 4) = *(v79 + 4 * *v11); /*0x5a113e*/
          *(v11[2] + 4 * (*v11)--) = 0; /*0x5a1148*/
          sub_5AD870(1); /*0x5a1154*/
          v75 = v80; /*0x5a115b*/
          if ( !v80 ) /*0x5a115d*/
            break; /*0x5a115d*/
          continue; /*0x5a115d*/
        }
      }
    }
  }
  operator delete(pMapCoord__4); /*0x5a115f*/
  if ( v11 ) /*0x5a116e*/
    sub_5AC340(v11, 1); /*0x5a1174*/
  return pFoundationData_3; /*0x5a117d*/
}