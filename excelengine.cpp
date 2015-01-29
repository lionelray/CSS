#include "excelengine.h"

ExcelEngine::ExcelEngine(QObject *parent) :
    QObject(parent)
{
}

ExcelEngine::ExcelEngine(QString xlsFile)
{
    pExcel     = NULL;
    pWorkbooks = NULL;
    pWorkbook  = NULL;
    pWorksheet = NULL;

    sXlsFile     = xlsFile;
    nRowCount    = 0;
    nColumnCount = 0;
    nStartRow    = 0;
    nStartColumn = 0;

    bIsOpen     = false;
    bIsValid    = false;
    bIsANewFile = false;
    bIsSaveAlready = false;
}

ExcelEngine::~ExcelEngine()
{
    if ( bIsOpen )
    {
        Close();
    }
    //    OleUninitialize();
}

bool ExcelEngine::Open(uint nSheet, bool visible)
{
    if ( bIsOpen )
    {
        //return bIsOpen;
        Close();
    }

    nCurrSheet = nSheet;
    bIsVisible = visible;

    if ( NULL == pExcel )
    {
        pExcel = new QAxObject("Excel.Application");
        if ( pExcel )
        {
            bIsValid = true;
        }
        else
        {
            bIsValid = false;
            bIsOpen  = false;
            return bIsOpen;
        }

        pExcel->dynamicCall("SetVisible(bool)", bIsVisible);
    }

    if ( !bIsValid )
    {
        bIsOpen  = false;
        return bIsOpen;
    }

    if ( sXlsFile.isEmpty() )
    {
        bIsOpen  = false;
        return bIsOpen;
    }

    QFile f(sXlsFile);
    if (!f.exists())
    {
        bIsANewFile = true;
    }
    else
    {
        bIsANewFile = false;
    }

    if (!bIsANewFile)
    {
        pWorkbooks = pExcel->querySubObject("WorkBooks"); //获取工作簿
        pWorkbook = pWorkbooks->querySubObject("Open(QString, QVariant)",sXlsFile,QVariant(0)); //打开xls对应的工作簿
    }
    else
    {
        pWorkbooks = pExcel->querySubObject("WorkBooks");     //获取工作簿
        pWorkbooks->dynamicCall("Add");                       //添加一个新的工作薄
        pWorkbook  = pExcel->querySubObject("ActiveWorkBook"); //新建一个xls
    }

    pWorksheet = pWorkbook->querySubObject("WorkSheets(int)", nCurrSheet);//打开第一个sheet

    //至此已打开，开始获取相应属性
    QAxObject *usedrange = pWorksheet->querySubObject("UsedRange");//获取该sheet的使用范围对象
    QAxObject *rows = usedrange->querySubObject("Rows");
    QAxObject *columns = usedrange->querySubObject("Columns");

    //因为excel可以从任意行列填数据而不一定是从0,0开始，因此要获取首行列下标
    nStartRow    = usedrange->property("Row").toInt();    //第一行的起始位置
    nStartColumn = usedrange->property("Column").toInt(); //第一列的起始位置

    nRowCount    = rows->property("Count").toInt();       //获取行数
    nColumnCount = columns->property("Count").toInt();    //获取列数

    bIsOpen  = true;
    return bIsOpen;
}
/**
  *@brief Open()的重载函数
  */
bool ExcelEngine::Open(QString xlsFile, uint nSheet, bool visible)
{
    sXlsFile = xlsFile;
    nCurrSheet = nSheet;
    bIsVisible = visible;

    return Open(nCurrSheet,bIsVisible);
}
/**
  *@brief 保存表格数据，把数据写入文件
  */
void ExcelEngine::Save()
{
    if ( pWorkbook )
    {
        if (bIsSaveAlready)
        {
            return ;
        }

        if (!bIsANewFile)
        {
            pWorkbook->dynamicCall("Save()");
        }
        else /*如果该文档是新建出来的，则使用另存为COM接口*/
        {
            pWorkbook->dynamicCall("SaveAs (const QString&,int,const QString&,const QString&,bool,bool)",
                                   sXlsFile,56,QString(""),QString(""),false,false);

        }

        bIsSaveAlready = true;
    }
}

/**
  *@brief 关闭前先保存数据，然后关闭当前Excel COM对象，并释放内存
  */
void ExcelEngine::Close()
{
    //关闭前先保存数据
    Save();

    if ( pExcel && pWorkbook )
    {
        pWorkbook->dynamicCall("Close(bool)", true);
        pExcel->dynamicCall("Quit()");

        delete pExcel;
        pExcel = NULL;

        bIsOpen     = false;
        bIsValid    = false;
        bIsANewFile = false;
        bIsSaveAlready = true;
    }
}

bool ExcelEngine::SaveDataFrTable(QTableView *tableView)
{
    if ( NULL == tableView )
    {
        return false;
    }
    if ( !bIsOpen )
    {
        return false;
    }

    int tableR = tableView->model()->rowCount();
    int tableC = tableView->model()->columnCount();

    //获取表头写做第一行
    for (int i=0; i<tableC; i++)
    {
        if ( tableView->model()->headerData(i,Qt::Horizontal,Qt::DisplayRole) != NULL )
        {
            this->SetCellData(1,i+1,tableView->model()->headerData(i,Qt::Horizontal,Qt::DisplayRole).toString());
            pWorksheet->querySubObject("Cells(int,int)",1,i+1)->setProperty("HorizontalAlignment", -4108); // 表头居中显示
        }
    }

    int ColWidth[20] = {0};
    //写数据
    for (int i=0; i<tableR; i++)
    {
        for (int j=0; j<tableC; j++)
        {
            if ( tableView->model()->index(i,j).data() != NULL )
            {                //                    QSqlQueryModel model(NULL);
                QModelIndex index = tableView->model()->index(i,j,QModelIndex());
                if (!isNumber(index) && (0 == ColWidth[j] || 2*index.data().toString().length() > ColWidth[j]))
                {
                    ColWidth[j] = 2*index.data().toString().length();
                    this->SetCellData(i+2,j+1,index.data().toString(), ColWidth[j]);
                }
                else
                {                    //                     model
                    this->SetCellData(i+2,j+1,index.data().toString());
                }
            }
        }
    }

    //保存
    Save();

    return true;
}
bool ExcelEngine::isNumber(QModelIndex index)
{
    QString sCheck = index.data().toString();
    QByteArray ba = sCheck.toLatin1();//QString 转换为 char*
         const char *s = ba.data();

        while(*s && *s>='0' && *s<='9') s++;

        if (*s)
        { //不是纯数字
            return false;
        }
        else
        { //纯数字
            return true;
        }
}
/**
  *@brief 修改指定单元格的数据
  *@param row : 单元格的行号
  *@param column : 单元格指定的列号
  *@param data : 单元格要修改为的新数据
  *@return 修改是否成功 true : 成功
  *                   false: 失败
  */
bool ExcelEngine::ReadDataToTable(QTableView *tableView)
{/*
    if ( NULL == tableView )
        {
            return false;
        }

        //先把table的内容清空
        int tableColumn = tableView->model()->columnCount();
        tableView->model()->;
        for (int n=0; n<tableColumn; n++)
        {
            tableView->removeColumn(0);
        }

        int rowcnt    = nStartRow + nRowCount;
        int columncnt = nStartColumn + nColumnCount;

        //获取excel中的第一行数据作为表头
        QStringList headerList;
        for (int n = nStartColumn; n<columncnt; n++ )
        {
            QAxObject * cell = pWorksheet->querySubObject("Cells(int,int)",nStartRow, n);
            if ( cell )
            {
                headerList<<cell->dynamicCall("Value2()").toString();
            }
        }

        //重新创建表头
        tableView->model()->setColumnCount(nColumnCount);
        tableView->setHorizontalHeaderLabels(headerList);


        //插入新数据
        for (int i = nStartRow+1, r = 0; i < rowcnt; i++, r++ )  //行
        {
            tableView->insertRow(r); //插入新行
            for (int j = nStartColumn, c = 0; j < columncnt; j++, c++ )  //列
            {
                QAxObject * cell = pWorksheet->querySubObject("Cells(int,int)", i, j );//获取单元格

                //在r新行中添加子项数据
                if ( cell )
                {
                    tableView->setItem(r,c,new QTableWidgetItem(cell->dynamicCall("Value2()").toString()));
                }
            }
        }

        return true;*/
}
/**
  *@brief 获取指定单元格的数据
  *@param row : 单元格的行号
  *@param column : 单元格的列号
  *@return [row,column]单元格对应的数据
  */
QVariant ExcelEngine::GetCellData(uint row, uint column)
{
    QVariant data;
    QAxObject *cell = pWorksheet->querySubObject("Cells(int,int)",row,column);//获取单元格对象
    if ( cell )
    {
        data = cell->dynamicCall("Value2()");
    }
    return data;
}
/**
  *@brief 修改指定单元格的数据
  *@param row : 单元格的行号
  *@param column : 单元格指定的列号
  *@param data : 单元格要修改为的新数据
  *@return 修改是否成功 true : 成功
  *                   false: 失败
  */
bool ExcelEngine::SetCellData(uint row, uint column, QVariant data)
{
    bool op = false;

    QAxObject *cell = pWorksheet->querySubObject("Cells(int,int)",row,column);//获取单元格对象
    if ( cell )
    {
        QString strData = data.toString(); //excel 居然只能插入字符串和整型，浮点型无法插入
        cell->dynamicCall("SetValue(const QVariant&)",strData); //修改单元格的数据
        op = true;
    }
    else
    {
        op = false;
    }

    return op;
}

bool ExcelEngine::SetCellData(uint row, uint column, QVariant data, int nColWidth)
{
    bool op = false;

    QAxObject *cell = pWorksheet->querySubObject("Cells(int,int)",row,column);//获取单元格对象
    if ( cell )
    {
        QString strData = data.toString(); //excel 居然只能插入字符串和整型，浮点型无法插入
        cell->dynamicCall("SetValue(const QVariant&)",strData); //修改单元格的数据
        op = true;
        cell->setProperty("ColumnWidth", nColWidth);
    }
    else
    {
        op = false;
    }

    return op;
}

/**
  *@brief 获取excel的行数
  */
uint ExcelEngine::GetRowCount() const
{
    return nRowCount;
}
/**
  *@brief 获取excel的列数
  */
uint ExcelEngine::GetColumnCount() const
{
    return nColumnCount;
}
/**
  *@brief 判断excel是否已被打开
  *@return true : 已打开
  *        false: 未打开
  */
bool ExcelEngine::IsOpen()
{
    return bIsOpen;
}
/**
  *@brief 判断excel COM对象是否调用成功，excel是否可用
  *@return true : 可用
  *        false: 不可用
  */
bool ExcelEngine::IsValid()
{
    return bIsValid;
}
/**
  *@brief 清空除报表之外的数据
  */
void ExcelEngine::Clear()
{
    sXlsFile     = "";
    nRowCount    = 0;
    nColumnCount = 0;
    nStartRow    = 0;
    nStartColumn = 0;
}
