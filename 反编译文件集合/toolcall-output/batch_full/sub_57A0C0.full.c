char __stdcall sub_57A0C0(int a1, int a2)
{
  int v2; // esi
  void *v3; // eax
  void *v4; // ebx
  int v5; // esi
  _DWORD *v6; // edi
  int v7; // esi
  int v8; // esi
  int i; // edi
  int v10; // eax
  CellClass *v11; // eax
  char j; // bl
  CellClass *k; // eax
  CellClass *m; // eax
  CellClass *n; // eax
  char v17; // [esp+13h] [ebp-1h]

  sub_4A8BF0(&MouseClass::Instance, 0);
  v17 = 0;
  if ( !dword_ABED10 )
  {
    v2 = dword_89C2DC * dword_89C2DC;
    v3 = operator new(80 * dword_89C2DC * dword_89C2DC);
    v4 = v3;
    if ( v3 )
    {
      v5 = v2 - 1;
      v6 = v3;
      if ( v5 >= 0 )
      {
        v7 = v5 + 1;
        do
        {
          sub_58BDC0(v6);
          v6 += 20;
          --v7;
        }
        while ( v7 );
      }
      dword_ABED10 = v4;
    }
    else
    {
      dword_ABED10 = 0;
    }
    v17 = 1;
  }
  v8 = 0;
  for ( i = dword_89C2DC * dword_89C2DC; v8 < i; *(v10 + 64) = -1 )
    v10 = sub_58C2C0(v8++);
  MouseClass::Instance.CellIterator_NextY = MouseClass::Instance.MapRect.Width;
  MouseClass::Instance.CellIterator_NextX = 1;
  MouseClass::Instance.CellIterator_CurrentY = MouseClass::Instance.MapRect.Width - 1;
  MouseClass::Instance.CellIterator_NextCell = &MouseClass::Instance.Cells.Items[512
                                                                               * MouseClass::Instance.MapRect.Width
                                                                               + 1];
  v11 = MapClass::CellIteratorNext(&MouseClass::Instance);
  for ( j = 1; v11; v11 = MapClass::CellIteratorNext(&MouseClass::Instance) )
  {
    if ( !j )
      break;
    j = sub_57A430(v11, a1, a2);
  }
  MouseClass::Instance.CellIterator_NextY = MouseClass::Instance.MapRect.Width;
  MouseClass::Instance.CellIterator_NextX = 1;
  MouseClass::Instance.CellIterator_CurrentY = MouseClass::Instance.MapRect.Width - 1;
  MouseClass::Instance.CellIterator_NextCell = &MouseClass::Instance.Cells.Items[512
                                                                               * MouseClass::Instance.MapRect.Width
                                                                               + 1];
  for ( k = MapClass::CellIteratorNext(&MouseClass::Instance); k; k = MapClass::CellIteratorNext(&MouseClass::Instance) )
  {
    if ( !j )
      break;
    sub_57A320(k, a1, a2);
  }
  MouseClass::Instance.CellIterator_NextY = MouseClass::Instance.MapRect.Width;
  MouseClass::Instance.CellIterator_NextX = 1;
  MouseClass::Instance.CellIterator_CurrentY = MouseClass::Instance.MapRect.Width - 1;
  MouseClass::Instance.CellIterator_NextCell = &MouseClass::Instance.Cells.Items[512
                                                                               * MouseClass::Instance.MapRect.Width
                                                                               + 1];
  for ( m = MapClass::CellIteratorNext(&MouseClass::Instance); m; m = MapClass::CellIteratorNext(&MouseClass::Instance) )
  {
    if ( !j )
      break;
    j = sub_57ACF0(m, 1, a1, a2);
  }
  MouseClass::Instance.CellIterator_NextY = MouseClass::Instance.MapRect.Width;
  MouseClass::Instance.CellIterator_NextX = 1;
  MouseClass::Instance.CellIterator_CurrentY = MouseClass::Instance.MapRect.Width - 1;
  MouseClass::Instance.CellIterator_NextCell = &MouseClass::Instance.Cells.Items[512
                                                                               * MouseClass::Instance.MapRect.Width
                                                                               + 1];
  for ( n = MapClass::CellIteratorNext(&MouseClass::Instance); n; n = MapClass::CellIteratorNext(&MouseClass::Instance) )
  {
    if ( !j )
      break;
    j = sub_57ACF0(n, 2, a1, a2);
  }
  MouseClass::Instance.CurrentBuildingType = 0;
  if ( MouseClass::Instance.CurrentBuilding )
  {
    (MouseClass::Instance.CurrentBuilding->~AbstractClass)(MouseClass::Instance.CurrentBuilding, 1);
    MouseClass::Instance.CurrentBuilding = 0;
  }
  if ( v17 )
  {
    operator delete(dword_ABED10);
    dword_ABED10 = 0;
  }
  return j;
}
