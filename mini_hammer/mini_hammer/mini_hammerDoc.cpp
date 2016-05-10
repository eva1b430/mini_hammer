
// mini_hammerDoc.cpp : implementation of the Cmini_hammerDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "mini_hammer.h"
#endif

#include "mini_hammerDoc.h"
#include "GlobalVar.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Cmini_hammerDoc

IMPLEMENT_DYNCREATE(Cmini_hammerDoc, CDocument)

BEGIN_MESSAGE_MAP(Cmini_hammerDoc, CDocument)
END_MESSAGE_MAP()


// Cmini_hammerDoc construction/destruction

Cmini_hammerDoc::Cmini_hammerDoc()
{
	// TODO: add one-time construction code here

}

Cmini_hammerDoc::~Cmini_hammerDoc()
{
}

BOOL Cmini_hammerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// Cmini_hammerDoc serialization

void Cmini_hammerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		CFile *pFile = ar.GetFile();
		CString strPath = pFile->GetFilePath();
		pFile->Close();

		Pathfinder* pFinder = GlobalVar::instance().GetPathfinder();
		if (pFinder)
		{
			pFinder->Save(strPath.GetBuffer());
		}

		pFile->Open(strPath, CFile::modeReadWrite);
	}
	else
	{
		// TODO: add loading code here
		CFile *pFile = ar.GetFile();
		CString strPath = pFile->GetFilePath();
		pFile->Close();

		Pathfinder* pFinder = GlobalVar::instance().GetPathfinder();
		if (pFinder)
		{
			pFinder->Load(strPath.GetBuffer());
		}

		pFile->Open(strPath, CFile::modeReadWrite);
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void Cmini_hammerDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void Cmini_hammerDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void Cmini_hammerDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Cmini_hammerDoc diagnostics

#ifdef _DEBUG
void Cmini_hammerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void Cmini_hammerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}

#endif //_DEBUG


// Cmini_hammerDoc commands
