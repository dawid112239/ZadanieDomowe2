#include<Windows.h>
#include<stdio.h>
#include "res.h"
#include <cstdlib>

int liczba_prob=0, liczba_wylosowana, liczba_podana;
CHAR szText[5];



INT_PTR CALLBACK DialogProc(HWND hwndDig, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
  case WM_COMMAND:
    switch (HIWORD(wParam))
    {
    case BN_CLICKED:
      switch (LOWORD(wParam))
      {
      case IDC_BUTTON1:
        liczba_prob++;
        CHAR Text[30];

        HWND hwndEditBox = GetDlgItem(hwndDig, IDC_EDIT1), hwndStatic1 = GetDlgItem(hwndDig, IDC_STATIC1), hwndStatic2 = GetDlgItem(hwndDig, IDC_STATIC2);
        int iTextLength = GetWindowTextLength(hwndEditBox);
        liczba_podana = atoi(szText);
        if (iTextLength > 0 && iTextLength < 3 && liczba_podana > 0 && liczba_podana < 41)
        {
          if (liczba_wylosowana == liczba_podana)
          {
            wsprintf(Text, "Wygra³eœ w %d kroku", liczba_prob);
            SetWindowText(hwndStatic1, Text);
            SetWindowText(hwndStatic2, "Gratulacje !!!!! Aby zagraæ ponownie wpisz liczbê i wciœnij Zagraj");
            liczba_wylosowana = (std::rand() % 40) + 1;
            liczba_prob = 0;
          }
          else
          {
            if (liczba_podana > liczba_wylosowana) {
              SetWindowText(hwndStatic1, "Wylosowana liczba jest mniejsza");
              wsprintf(Text, "Krok: %d ", liczba_prob);
              SetWindowText(hwndStatic2, Text);
            }
            else {
              SetWindowText(hwndStatic1, "Wylosowana liczba jest wiêksza");
              wsprintf(Text, "Krok: %d", liczba_prob);
              SetWindowText(hwndStatic2, Text);
            }
          }
        }
        else 
        {
          SetWindowText(hwndStatic1, "Niepoprawne dane wpisz liczbê z zakresu 1-40");
          liczba_prob--;
        }
        return TRUE;
      }
      return FALSE;
    case EN_CHANGE:
      switch (LOWORD(wParam))
      {
      case IDC_EDIT1:

        HWND hwndEditBox = GetDlgItem(hwndDig, IDC_EDIT1);
        GetWindowText(hwndEditBox, szText, 3);
        return TRUE;
        
      }
      return FALSE;
    }
    return FALSE;
  case WM_CLOSE:
    DestroyWindow(hwndDig);
    PostQuitMessage(0);
    return TRUE;
  }
  return FALSE;
}


int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevinstance, PSTR szCmdLIne, int iCmdShow)
{
  liczba_wylosowana = (std::rand() % 40) + 1;
  HWND hwndMainWindow = CreateDialog(hinstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
  ShowWindow(hwndMainWindow, iCmdShow);
  MSG msg = {};

  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}
