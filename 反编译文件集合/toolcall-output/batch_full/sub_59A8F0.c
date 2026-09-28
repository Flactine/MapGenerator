void __stdcall sub_59A8F0(void ***p_p_??_7?$DynamicVectorClass@V?$TRect@H@@@@6B@, signed int a2, int *a3)
{
  double number; // st7
  int v4; // eax
  int v5; // ebx
  int v6; // esi
  int *v7; // ebp
  int v8; // esi
  int v9; // edi
  unsigned int v10; // ecx
  int v11; // eax
  int v12; // eax
  int v13; // edi
  unsigned int v14; // esi
  signed int v15; // eax
  int v16; // edi
  int v17; // ecx
  void **v18; // eax
  void **v19; // ecx
  void **v20; // eax
  void **v21; // edx
  bool v22; // zf
  int v23; // [esp+18h] [ebp-74h]
  int v24; // [esp+1Ch] [ebp-70h]
  __int64 v25; // [esp+20h] [ebp-6Ch]
  int v26; // [esp+28h] [ebp-64h]
  int v27; // [esp+2Ch] [ebp-60h]
  int v28; // [esp+30h] [ebp-5Ch]
  int v29; // [esp+38h] [ebp-54h]
  int v30; // [esp+3Ch] [ebp-50h]
  int v31; // [esp+40h] [ebp-4Ch]
  int j; // [esp+40h] [ebp-4Ch]
  int v33; // [esp+44h] [ebp-48h]
  int v34; // [esp+48h] [ebp-44h]
  __int64 v35; // [esp+4Ch] [ebp-40h]
  double v36; // [esp+54h] [ebp-38h]
  CDTimerClass_vtbl *p_??_7?$DynamicVectorClass@H@@6B@_1; // [esp+5Ch] [ebp-30h] BYREF
  void *Block; // [esp+60h] [ebp-2Ch]
  int v39; // [esp+64h] [ebp-28h]
  int v40; // [esp+68h] [ebp-24h]
  int i; // [esp+6Ch] [ebp-20h]
  int n10_1; // [esp+70h] [ebp-1Ch]
  CDTimerClass_vtbl *p_??_7?$DynamicVectorClass@H@@6B@; // [esp+74h] [ebp-18h] BYREF
  void *v44; // [esp+78h] [ebp-14h]
  int v45; // [esp+7Ch] [ebp-10h]
  char v46; // [esp+81h] [ebp-Bh]
  int v47; // [esp+84h] [ebp-8h]
  int n10; // [esp+88h] [ebp-4h]

  number = YRMath::sqrt(a2); /*0x59a901*/
  v4 = Game::F2I64(number); /*0x59a909*/
  v31 = v4; /*0x59a91c*/
  if ( v4 * v4 == a2 ) /*0x59a920*/
  {
    v5 = v4; /*0x59a922*/
    v26 = v4; /*0x59a924*/
  }
  else
  {
    v26 = v4 + 1; /*0x59a92d*/
    v5 = v4 + 1; /*0x59a931*/
  }
  if ( v4 * v5 < a2 ) /*0x59a93a*/
  {
    v23 = v5; /*0x59a944*/
    v6 = v5; /*0x59a948*/
  }
  else
  {
    v6 = v4; /*0x59a93c*/
    v23 = v4; /*0x59a93e*/
  }
  v7 = a3; /*0x59a94a*/
  v24 = a3[2] / v5; /*0x59a95c*/
  v25 = (a3[3] / v5); /*0x59a966*/
  v29 = 0; /*0x59a96c*/
  v30 = 0; /*0x59a970*/
  v27 = 0; /*0x59a978*/
  if ( Randomizer::Random(&dst_) * 2.328306437080797e-10 >= 0.5 ) /*0x59a9a2*/
  {
    HIDWORD(v25) = v24; /*0x59a9c6*/
    LODWORD(v25) = a3[3] / v6; /*0x59a9ca*/
    v30 = v25; /*0x59a9ce*/
  }
  else
  {
    v27 = v25; /*0x59a9ae*/
    v24 = a3[2] / v6; /*0x59a9b2*/
    v29 = v24; /*0x59a9b6*/
  }
  v8 = v5 * v6 - a2; /*0x59a9db*/
  v9 = 0; /*0x59a9dd*/
  v34 = a3[1]; /*0x59a9df*/
  v33 = *a3; /*0x59a9e9*/
  sub_477BE0(&p_??_7?$DynamicVectorClass@H@@6B@, 0, 0); /*0x59a9ed*/
  p_??_7?$DynamicVectorClass@H@@6B@ = &DynamicVectorClass<int>::`vftable'; /*0x59a9f8*/
  n10 = 10; /*0x59aa00*/
  v47 = 0; /*0x59aa0b*/
  sub_477BE0(&p_??_7?$DynamicVectorClass@H@@6B@_1, 0, 0); /*0x59aa12*/
  v10 = 0; /*0x59aa1b*/
  p_??_7?$DynamicVectorClass@H@@6B@_1 = &DynamicVectorClass<int>::`vftable'; /*0x59aa1f*/
  n10_1 = 10; /*0x59aa27*/
  i = 0; /*0x59aa2f*/
  if ( v23 > 0 ) /*0x59aa33*/
  {
    do /*0x59aacf*/
    {
      if ( v47 < v45 /*0x59aa69*/
        || (v46 || !v45)
        && n10 > 0
        && (p_??_7?$DynamicVectorClass@H@@6B@->sub_477C70)(&p_??_7?$DynamicVectorClass@H@@6B@, n10 + v45, 0) )
      {
        v11 = v47++; /*0x59aa74*/
        *(v44 + v11) = v5; /*0x59aa7f*/
      }
      if ( i < v39 /*0x59aaaf*/
        || (BYTE1(v40) || !v39)
        && n10_1 > 0
        && (p_??_7?$DynamicVectorClass@H@@6B@_1->sub_477C70)(&p_??_7?$DynamicVectorClass@H@@6B@_1, n10_1 + v39, 0) )
      {
        v12 = i++; /*0x59aaba*/
        *(Block + v12) = v9; /*0x59aac5*/
      }
      ++v9; /*0x59aacc*/
    }
    while ( v9 < v23 ); /*0x59aacf*/
    v10 = i; /*0x59aad5*/
  }
  if ( v8 > 0 ) /*0x59aadb*/
  {
    v13 = v8; /*0x59aae1*/
    do /*0x59ab62*/
    {
      v14 = v10 - 1; /*0x59aae3*/
      v36 = v10; /*0x59aaf9*/
      do /*0x59ab28*/
      {
        v35 = Randomizer::Random(&dst_); /*0x59ab07*/
        v15 = Game::F2I64(v35 * v36 * 2.328306437080797e-10); /*0x59ab21*/
      }
      while ( v15 > v14 ); /*0x59ab28*/
      *(v44 + *(Block + v15)) = v31; /*0x59ab39*/
      v10 = i; /*0x59ab3c*/
      if ( v15 < i ) /*0x59ab42*/
      {
        v10 = i - 1; /*0x59ab44*/
        for ( i = v10; v15 < i; v10 = i ) /*0x59ab4b*/
        {
          ++v15; /*0x59ab51*/
          *(Block + v15 - 1) = *(Block + v15); /*0x59ab55*/
        }
      }
      --v13; /*0x59ab61*/
    }
    while ( v13 ); /*0x59ab62*/
  }
  v16 = 0; /*0x59ab6c*/
  for ( j = 0; v16 < v23; j = v16 ) /*0x59ab74*/
  {
    v17 = *(v44 + v16); /*0x59ab85*/
    if ( v17 < v5 ) /*0x59ab8a*/
    {
      if ( SHIDWORD(v25) <= 0 ) /*0x59ab92*/
        v34 += v25 / 2; /*0x59abb8*/
      else
        v33 += v24 / 2; /*0x59aba3*/
    }
    if ( v17 > 0 ) /*0x59abbe*/
    {
      v28 = *(v44 + v16); /*0x59abc8*/
      do /*0x59ac53*/
      {
        v18 = p_p_??_7?$DynamicVectorClass@V?$TRect@H@@@@6B@[2]; /*0x59abda*/
        if ( p_p_??_7?$DynamicVectorClass@V?$TRect@H@@@@6B@[4] < v18 /*0x59ac02*/
          || (*(p_p_??_7?$DynamicVectorClass@V?$TRect@H@@@@6B@ + 13) || !v18)
          && (v19 = p_p_??_7?$DynamicVectorClass@V?$TRect@H@@@@6B@[5], v19 > 0)
          && ((*p_p_??_7?$DynamicVectorClass@V?$TRect@H@@@@6B@)[2])(
               p_p_??_7?$DynamicVectorClass@V?$TRect@H@@@@6B@,
               v19 + v18,
               0) )
        {
          v20 = p_p_??_7?$DynamicVectorClass@V?$TRect@H@@@@6B@[4]; /*0x59ac09*/
          p_p_??_7?$DynamicVectorClass@V?$TRect@H@@@@6B@[4] = (v20 + 1); /*0x59ac0f*/
          v21 = &p_p_??_7?$DynamicVectorClass@V?$TRect@H@@@@6B@[1][4 * v20]; /*0x59ac1a*/
          *v21 = (v33 + 2); /*0x59ac23*/
          v21[1] = (v34 + 2); /*0x59ac25*/
          v21[2] = (v24 - 4); /*0x59ac28*/
          v21[3] = (v25 - 4); /*0x59ac2b*/
        }
        v33 += HIDWORD(v25); /*0x59ac40*/
        v22 = v28 == 1; /*0x59ac4a*/
        v34 += v27; /*0x59ac4b*/
        --v28; /*0x59ac4f*/
      }
      while ( !v22 ); /*0x59ac53*/
      v5 = v26; /*0x59ac59*/
      v7 = a3; /*0x59ac5d*/
      v16 = j; /*0x59ac64*/
    }
    v33 += v29; /*0x59ac7a*/
    v34 += v30; /*0x59ac86*/
    if ( SHIDWORD(v25) <= 0 ) /*0x59ac8a*/
      v34 = v7[1]; /*0x59ac98*/
    else
      v33 = *v7; /*0x59ac8f*/
    ++v16; /*0x59aca0*/
  }
  p_??_7?$DynamicVectorClass@H@@6B@_1 = &CDTimerClass_vtbl_; /*0x59acb8*/
  if ( Block && BYTE1(v40) ) /*0x59acc4*/
  {
    operator delete(Block); /*0x59acc7*/
    Block = 0; /*0x59accf*/
  }
  p_??_7?$DynamicVectorClass@H@@6B@ = &CDTimerClass_vtbl_; /*0x59acdb*/
  BYTE1(v40) = 0; /*0x59ace2*/
  v39 = 0; /*0x59ace9*/
  if ( v44 ) /*0x59acf2*/
  {
    if ( v46 ) /*0x59acfa*/
      operator delete(v44); /*0x59acfd*/
  }
}