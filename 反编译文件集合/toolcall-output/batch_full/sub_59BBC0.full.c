int __thiscall sub_59BBC0(int *this, int n400_1, _DWORD *a3, int p_n2, int a5, int p_MapCoords, double a7, char a8)
{
  int n400; // eax
  int n100; // edi
  void *v10; // eax
  int *v11; // eax
  int *v12; // esi
  void *v13; // eax
  int v14; // ecx
  int v15; // eax
  unsigned int v16; // ebx
  unsigned int v17; // eax
  __int16 v18; // di
  unsigned int v19; // ebx
  unsigned int v20; // eax
  __int16 v21; // cx
  __int16 v22; // ax
  CellClass *v23; // eax
  int n400_3; // eax
  __int16 v25; // dx
  int pMapCoord__3; // eax
  int v27; // edx
  int v28; // eax
  _DWORD *v29; // edi
  unsigned int v30; // ecx
  unsigned int v31; // edx
  int v32; // ebx
  unsigned int v33; // eax
  CellStruct *pMapCoord; // edi
  int v35; // eax
  double v36; // st6
  CellClass *CellAt_MapCrd; // eax
  char *v38; // ecx
  int n100_3; // edx
  int Width; // ebx
  char v41; // al
  int v42; // eax
  __int16 v43; // cx
  int v44; // eax
  int Width_1; // ecx
  char *v46; // edi
  CellClass *v47; // eax
  unsigned int v48; // ebx
  double number; // st7
  __int16 v50; // ax
  double v51; // st7
  __int16 v52; // ax
  int n100_4; // ecx
  unsigned int v54; // eax
  unsigned int v55; // ecx
  unsigned int v56; // edi
  unsigned int v57; // edx
  int v58; // edi
  int v59; // ebx
  unsigned int v60; // ecx
  double v61; // st7
  double v62; // st7
  int v63; // ecx
  bool v64; // zf
  int v65; // eax
  int v66; // eax
  CellStruct *pMapCoord_2; // edi
  CellClass *v68; // ebx
  char *v69; // edi
  int v70; // eax
  CellClass *i; // eax
  int IsoTileTypeIndex; // ecx
  int nIdx; // esi
  int v74; // edi
  CellClass *j; // eax
  char *v76; // ecx
  char v77; // [esp+17h] [ebp-81h]
  int pMapCoord__1; // [esp+1Ch] [ebp-7Ch] BYREF
  int pMapCoord_; // [esp+20h] [ebp-78h] BYREF
  int n400_2; // [esp+24h] [ebp-74h]
  int n100_2; // [esp+28h] [ebp-70h]
  int pMapCoord_1; // [esp+2Ch] [ebp-6Ch]
  void *Block; // [esp+30h] [ebp-68h]
  float v85; // [esp+34h] [ebp-64h]
  float v86; // [esp+38h] [ebp-60h]
  int pMapCoord__2; // [esp+3Ch] [ebp-5Ch]
  int pMapCoord__4; // [esp+40h] [ebp-58h]
  int n100_1; // [esp+44h] [ebp-54h]
  __int64 v90; // [esp+48h] [ebp-50h]
  __int64 n8; // [esp+50h] [ebp-48h]
  int pMapCoord__5; // [esp+58h] [ebp-40h] BYREF
  float v93; // [esp+60h] [ebp-38h]
  double v94; // [esp+68h] [ebp-30h]
  double v95; // [esp+70h] [ebp-28h]
  double v96; // [esp+78h] [ebp-20h]
  double v97; // [esp+80h] [ebp-18h]
  double v98; // [esp+88h] [ebp-10h]
  double Height; // [esp+90h] [ebp-8h]

  n400 = n400_1;
  if ( n400_1 <= 400 )
  {
    n400 = 400;
    n400_1 = 400;
  }
  n100 = 8 * n400 + 2;
  if ( n100 <= 100 )
    n100 = 100;
  n100_1 = n100;
  v10 = operator new(8 * n100);
  if ( v10 )
  {
    Block = v10;
    LODWORD(v94) = n100 - 1;
  }
  else
  {
    Block = 0;
  }
  v11 = operator new(0x14u);
  v12 = v11;
  if ( v11 )
  {
    v11[3] = 0;
    v11[4] = -1;
    *v11 = 0;
    v11[1] = n100;
    v13 = operator new(4 * n100 + 4);
    v14 = v12[1];
    v12[2] = v13;
    v15 = 0;
    if ( v14 >= 0 )
    {
      do
      {
        ++v15;
        *(v12[2] + 4 * v15 - 4) = 0;
      }
      while ( v15 <= v12[1] );
    }
  }
  else
  {
    v12 = 0;
  }
  if ( *p_n2 || *(p_n2 + 4) )
  {
    v25 = *(p_n2 + 4);
    LOWORD(pMapCoord__2) = *p_n2;
    HIWORD(pMapCoord__2) = v25;
    pMapCoord__1 = pMapCoord__2;
LABEL_27:
    v86 = 0.0;
    v85 = 0.0;
    if ( *a3 != dword_ABE2F0 || a3[1] != dword_ABE2F4 || a3[2] != dword_ABE2F8 || a3[3] != dword_ABE2FC )
    {
      pMapCoord__3 = a3[3];
      pMapCoord_1 = a3[2];
      pMapCoord__2 = pMapCoord__3;
      if ( pMapCoord_1 <= pMapCoord__3 )
      {
        v85 = 1.0;
        v86 = pMapCoord__2 / pMapCoord_1 * 1.2;
      }
      else
      {
        v86 = 1.0;
        v85 = pMapCoord_1 / pMapCoord__2 * 1.2;
      }
    }
    LODWORD(n8) = pMapCoord__1;
    v27 = *v12;
    LODWORD(n8) = SHIWORD(pMapCoord__1);
    v28 = 0;
    v95 = pMapCoord__1;
    n400_2 = 0;
    v96 = SHIWORD(pMapCoord__1);
    if ( v27 >= 0 )
    {
      do
      {
        ++v28;
        *(v12[2] + 4 * v28 - 4) = 0;
      }
      while ( v28 <= *v12 );
    }
    v29 = Block;
    *v12 = 0;
    n100_2 = 1;
    *v29 = pMapCoord__1;
    v29[1] = 0;
    *(dword_ABED10 + 20 * pMapCoord__1 + 20 * dword_89C2DC * SHIWORD(pMapCoord__1) + 15) = this[194];
    v30 = *v12 + 1;
    LODWORD(n8) = v29[1];
    v31 = v30 >> 1;
    if ( v30 < v12[1] )
    {
      for ( ; v30 > 1; v31 >>= 1 )
      {
        v32 = v12[2];
        if ( *(*(v32 + 4 * v31) + 4) <= *&n8 )
          break;
        *(v32 + 4 * v30) = *(v32 + 4 * v31);
        v30 = v31;
      }
      *(v12[2] + 4 * v30) = v29;
      v33 = v12[3];
      ++*v12;
      if ( v29 > v33 )
        v12[3] = v29;
      if ( v29 < v12[4] )
        v12[4] = v29;
    }
    if ( *v12 )
    {
      v35 = v12[2];
      pMapCoord = *(v35 + 4);
      *(v35 + 4) = *(v35 + 4 * *v12);
      *(v12[2] + 4 * (*v12)--) = 0;
      sub_5AD870(1);
    }
    else
    {
      pMapCoord = 0;
    }
    pMapCoord_1 = pMapCoord;
    v36 = a3[2] * 0.5;
    v98 = 1.0 / (v36 * v36);
    v97 = 1.0 / (a3[3] * 0.5 * (a3[3] * 0.5));
    do
    {
      if ( !pMapCoord )
        break;
      if ( dword_ABED10 )
        *(dword_ABED10 + 20 * pMapCoord->X + 20 * dword_89C2DC * pMapCoord->Y + 14) = this[194];
      CellAt_MapCrd = MapClass::GetCellAt_MapCrd(&MouseClass::Instance, pMapCoord);
      v38 = Block;
      n100_3 = n100_2;
      CellAt_MapCrd->IsoTileTypeIndex = 0;
      Width = ::Width;
      v41 = 0;
      LODWORD(n8) = 0;
      LODWORD(v90) = &v38[8 * n100_3];
      while ( 1 )
      {
        v42 = v41 & 7;
        v43 = pMapCoord->Y + Neighbours[v42].Y;
        LOWORD(pMapCoord__4) = pMapCoord->X + Neighbours[v42].X;
        HIWORD(pMapCoord__4) = v43;
        pMapCoord_ = pMapCoord__4;
        v44 = v43;
        Width_1 = v43 + pMapCoord__4;
        if ( Width_1 > Width && pMapCoord__4 - v44 < Width && v44 - pMapCoord__4 < Width && Width_1 <= ::Width_1 )
        {
          v46 = dword_ABED10 + 80 * pMapCoord__4 + 80 * dword_89C2DC * v44;
          if ( !*(v46 + 14) && *(v46 + 15) != this[194] )
          {
            v47 = MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord_);
            if ( sub_4865D0(v47) && n100_2 < n100_1 && sub_59BAB0(&pMapCoord_, a3, a5, v98, v97) )
            {
              v48 = v90;
              number = v95 + 0.5;
              *v90 = pMapCoord_;
              v50 = Game::F2I64(number);
              v51 = v96 + 0.5;
              LOWORD(pMapCoord__2) = v50;
              v52 = Game::F2I64(v96 + 0.5);
              HIWORD(pMapCoord__2) = v52;
              pMapCoord__5 = pMapCoord__2;
              if ( a8 )
              {
                sub_59B940(&pMapCoord__5, &pMapCoord_, a3, p_MapCoords, v86, v85);
              }
              else
              {
                LODWORD(v90) = (SHIWORD(pMapCoord_) - v52) * (SHIWORD(pMapCoord_) - v52)
                             + (pMapCoord_ - pMapCoord__2) * (pMapCoord_ - pMapCoord__2);
                v94 = YRMath::sqrt(v90);
                *&Height = Randomizer::Random(&dst_);
                v51 = *&Height * 5.0 * 2.328306437080797e-10 + v94;
              }
              n100_4 = n100_2;
              *(v48 + 4) = v51;
              *(v46 + 15) = this[194];
              v54 = v48;
              n100_2 = n100_4 + 1;
              v55 = *v12 + 1;
              v93 = *(v48 + 4);
              v56 = v12[1];
              v57 = v55 >> 1;
              LODWORD(v94) = v48;
              LODWORD(v90) = v48 + 8;
              if ( v55 < v56 )
              {
                if ( v55 > 1 )
                {
                  do
                  {
                    v58 = v12[2];
                    v59 = *(v58 + 4 * v57);
                    if ( *(v59 + 4) <= v93 )
                      break;
                    *(v58 + 4 * v55) = v59;
                    v55 = v57;
                    v57 >>= 1;
                  }
                  while ( v55 > 1 );
                  v54 = LODWORD(v94);
                }
                *(v12[2] + 4 * v55) = v54;
                v60 = v12[3];
                ++*v12;
                if ( v54 > v60 )
                  v12[3] = v54;
                if ( v54 < v12[4] )
                  v12[4] = v54;
              }
            }
            Width = ::Width;
          }
        }
        v41 = n8 + 2;
        LODWORD(n8) = n8 + 2;
        if ( n8 >= 8 )
          break;
        pMapCoord = pMapCoord_1;
      }
      v61 = sub_5980C0(&dst__0);
      v95 = v61 * a7 + v95;
      v62 = sub_5980C0(&dst__0);
      ++n400_2;
      v63 = *v12;
      v64 = *v12 == 0;
      v96 = v62 * a7 + v96;
      if ( v64 )
      {
        pMapCoord = 0;
      }
      else
      {
        v65 = v12[2];
        pMapCoord = *(v65 + 4);
        *(v65 + 4) = *(v65 + 4 * v63);
        *(v12[2] + 4 * (*v12)--) = 0;
        sub_5AD870(1);
      }
      pMapCoord_1 = pMapCoord;
    }
    while ( n400_2 < n400_1 );
    if ( *v12 )
    {
      v66 = v12[2];
      pMapCoord_2 = *(v66 + 4);
      *(v66 + 4) = *(v66 + 4 * *v12);
      *(v12[2] + 4 * (*v12)--) = 0;
      sub_5AD870(1);
      for ( ; pMapCoord_2; ++n400_2 )
      {
        v68 = MapClass::GetCellAt_MapCrd(&MouseClass::Instance, pMapCoord_2);
        v69 = dword_ABED10 + 80 * pMapCoord_2->X + 80 * dword_89C2DC * pMapCoord_2->Y;
        if ( !*(v69 + 14) && sub_4865D0(v68) )
        {
          v68->IsoTileTypeIndex = 0;
          *(v69 + 14) = this[194];
        }
        if ( *v12 )
        {
          v70 = v12[2];
          pMapCoord_2 = *(v70 + 4);
          *(v70 + 4) = *(v70 + 4 * *v12);
          *(v12[2] + 4 * (*v12)--) = 0;
          sub_5AD870(1);
        }
        else
        {
          pMapCoord_2 = 0;
        }
      }
    }
    operator delete(Block);
    if ( v12 )
    {
      operator delete(v12[2]);
      operator delete(v12);
    }
    v77 = sub_57A0C0(this[194], 1);
    sub_578350(&MouseClass::Instance);
    for ( i = MapClass::CellIteratorNext(&MouseClass::Instance); i; i = MapClass::CellIteratorNext(&MouseClass::Instance) )
    {
      IsoTileTypeIndex = i->IsoTileTypeIndex;
      if ( IsoTileTypeIndex >= IsoTileTypeIndex_1 && IsoTileTypeIndex < IsoTileTypeIndex_1 + 42 )
      {
        i->IsoTileTypeIndex = 0;
        i->Height = 0;
      }
    }
    if ( v77 )
    {
      n400_3 = n400_2;
      ++this[194];
    }
    else
    {
      nIdx = ::nIdx;
      v74 = this[194];
      sub_578350(&MouseClass::Instance);
      for ( j = MapClass::CellIteratorNext(&MouseClass::Instance); j; j = MapClass::CellIteratorNext(&MouseClass::Instance) )
      {
        LODWORD(v94) = j->MapCoords;
        v76 = dword_ABED10 + 80 * SLOWORD(v94) + 80 * dword_89C2DC * SWORD1(v94);
        if ( *(v76 + 14) == v74 )
        {
          *(v76 + 14) = 0;
          v76[75] = 0;
          j->IsoTileTypeIndex = nIdx;
          j->Height = 0;
          j->Level = this[195];
        }
      }
      return 0;
    }
  }
  else
  {
    pMapCoord_1 = 0;
    while ( 1 )
    {
      v16 = MouseClass::Instance.MapRect.Width - 1;
      *&v96 = MouseClass::Instance.MapRect.Width;
      Height = MouseClass::Instance.MapRect.Width;
      do
      {
        *&v95 = Randomizer::Random(&dst_);
        v17 = Game::F2I64(*&v95 * Height * 2.328306437080797e-10);
        v18 = v17;
      }
      while ( v17 > v16 );
      v19 = MouseClass::Instance.MapRect.Height - 1;
      n8 = MouseClass::Instance.MapRect.Height;
      Height = MouseClass::Instance.MapRect.Height;
      do
      {
        v90 = Randomizer::Random(&dst_);
        v20 = Game::F2I64(v90 * Height * 2.328306437080797e-10);
      }
      while ( v20 > v19 );
      HIWORD(pMapCoord__5) = -v18;
      HIWORD(v93) = MouseClass::Instance.MapRect.Width;
      LOWORD(v94) = v18 + 1;
      WORD1(v94) = LOWORD(MouseClass::Instance.MapRect.Width) - v18;
      v21 = v20 + v18 + 1;
      v22 = LOWORD(MouseClass::Instance.MapRect.Width) - v18 + v20;
      LOWORD(pMapCoord__2) = v21;
      HIWORD(pMapCoord__2) = v22;
      pMapCoord__1 = pMapCoord__2;
      if ( ++pMapCoord_1 >= 200 )
        return 0;
      if ( dword_ABED10 )
      {
        if ( !*(dword_ABED10 + 20 * v21 + 20 * dword_89C2DC * v22 + 14) )
        {
          v23 = MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord__1);
          if ( sub_4865D0(v23) )
          {
            if ( pMapCoord_1 < 200 )
              goto LABEL_27;
            return 0;
          }
        }
      }
    }
  }
  return n400_3;
}
