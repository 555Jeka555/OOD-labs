Спроектировать архитектуру программы для редактирования электронных таблиц.

1. Каждая ячейка таблицы может быть пустой, либо содержать некоторое значение или формулу.
2. Формула может состоять из операций сложения, вычитания и умножения.
3. Аргументами формул могут быть как числа, так и ссылки на ячейки таблицы.
4. При изменении значений в ячейке, значения зависящих от неё ячеек должны автоматически обновляться.

```mermaid
classDiagram
    direction TB

    class ISpreadsheet {
        <<interface>>
        + SetValue(int row, int col, string value)
    }
    
    class Spreadsheet {
        - cells: Array~Array~CellCow~~
        %%обрабывает пришедщую value и складывает в ячейку
        + SetValue(int row, int col, string value)
        + GetCell(int row, int col) ICell
        + RegisterObservers(cell: ISpreadsheetObserver)
        + NotifyObserver()
        + RemoveObserver(cell: ISpreadsheetObserver)
    }
    ISpreadsheet <.. Spreadsheet  
    Spreadsheet *-- CellCow
    Spreadsheet --> ICellInSpreadsheet: Use

    class SpreedSheetPresenter {
        + Update(spreadsheet: Array~Array~ICellInSpreadsheet~~)
        + SetValue(int row, int col, string value)
        + ClickOnCell(int row, int col)
        - mCells: Array~Array~ICellInSpreadsheet~~
        -mTable: ISpreadsheet
    }

    class SpreedSheetView {
        + Update(spreadsheet: Array~Array~ICellInSpreadsheet~~)
        + SetValue(int row, int col, string value)
        - mCells: Array~Array~ICellInSpreadsheet~~
        -mTable: ISpreadsheet
    }
    
    SpreedSheetPresenter o-- ICellInSpreadsheet
    SpreedSheetPresenter o-- ISpreadsheet

    class ISpreadsheetObservable {
        + RegisterObservers(cell: ISpreadsheetObserver)
        + NotifyObserver()
        + RemoveObserver(cell: ISpreadsheetObserver)
    }
    

    class ISpreadsheetObserver {
        + Update(spreadsheet: Array~Array~ICellInSpreadsheet~~)
    }


 
    class Presenter {
        + Update(spreadsheet: Array~Array~ICellInSpreadsheet~~)
    }

    class ICellObservable {
        + RegisterObservers(cell: ICellObserver)
        + NotifyObserver()
        + RemoveObserver(cell: ICellObserver)
    }

    class ICellObserver {
        + Update()
    }
    
    class ICellInSpreadsheet {
        + GetValue(): string
        + GetFormula(): string
    }
    
    ICellInSpreadsheet <.. ICell

    class ICell {
        <<interface>>
        + GetValue(): string
        + GetFormula(): string
        + SetValue(value: string)
        + Clone(): ICell
        + RegisterObserver(cell: ICellObserver)
        + NotifyObserver()
        + RemoveObserver(cell: ICellObserver)
        + Update()
    }

    class Cell {
        - Value: CellValue
        %%прогоняет значение через парсер
        + SetValue(value: string)
        + GetValue(): string
        + Clone(): ICell
        + GetFormula(): string
        + Update()
    }
    
    class CellValue {
        mValue: String
        mFormula: String?
    }
    
    class CellCow {
        - mFormulaPrepare: FormulaPrepare
        - prepareValue()
        - Value: ICell
        - mCounter
        - Subscribers: List~ICellObserver~
        + GetValue(): string
        + GetFormula(): string
        + SetValue(value: string)
        + Clone(): ICell
        + RegisterObserver(cell: ICellObserver)
        + NotifyObserver()
        + RemoveObserver(cell: ICellObserver)
        + Update()
    }

    class FormulaPrepare {
        %%решает формулу и подписывает ячейку на изменение другие ячеек
        + Parse(string formula, cell: ICellObserver): CellValue
        - mSpreedSheet: SpreedSheet
    }
    FormulaPrepare --> CellValue: Use
    FormulaPrepare o-- Spreadsheet
    FormulaPrepare --> ICellObserver : Use
   
    Cell *-- CellValue
    ICell <.. Cell
    ICellObserver <.. ICell
    ICellInSpreadsheet <.. ICell
    ICellObservable <.. ICell  
    ICell <.. CellCow
    CellCow *-- ICell
    CellCow *-- FormulaPrepare
```
