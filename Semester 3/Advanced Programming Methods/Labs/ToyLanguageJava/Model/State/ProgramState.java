package Model.State;

import Collection.Heap.MyIHeap;
import Model.Statement.IStatement;
import Collection.Dictionary.MyDictionary;
import Collection.Dictionary.MyIDictionary;
import Collection.List.MyIList;
import Collection.List.MyList;
import Collection.Stack.MyIStack;
import Collection.Stack.MyStack;

import Model.Exception.ADTEmptyException;
import Model.Exception.ToyLanguageInterpreterException;
import Model.Value.Value;

import java.io.BufferedReader;
import java.util.List;

public class ProgramState {
    private MyIStack<IStatement> executionStack;
    private MyIDictionary<String, Value> symbolTable;
    private MyIList<Value> outputList;

    private MyIHeap heap;
    private MyIDictionary<String, BufferedReader> fileTable;

    private IStatement originalProgram;
    private MyIDictionary<Integer, Integer> heapTable;

    private int id;
    private static int lastID=0;

    public ProgramState(MyIStack<IStatement> programStateMyStack, MyIDictionary<String, Value> symbolTable, MyIList<Value> outputList, MyIDictionary<String, BufferedReader> fileTable, MyIHeap heap, IStatement originalProgram) {
        this.executionStack = programStateMyStack;
        this.symbolTable = symbolTable;
        this.outputList = outputList;
        this.originalProgram = originalProgram;
        this.fileTable = fileTable;
        this.heap=heap;


        executionStack.push(originalProgram);
    }

    public ProgramState(IStatement originalProgram) {
        executionStack = new MyStack<>();
        symbolTable = new MyDictionary<>();
        this.originalProgram = originalProgram;

        executionStack.push(originalProgram);
    }
    public ProgramState(MyIStack<IStatement> newStack, MyIDictionary<String, Value> newSymTable, MyIList<Value> outputList, MyIDictionary<String, BufferedReader> fileTable, MyIHeap heap) {
        this.executionStack = newStack;
        this.symbolTable = newSymTable;
        this.outputList = outputList;
        this.fileTable = fileTable;
        this.heap = heap;
        this.id=setID();
    }

    public synchronized int setID(){
        lastID++;
        return lastID;
    }

    public void sID(){
        id=setID();
    }
    public MyIStack<IStatement> getExecutionStack() {
        return executionStack;
    }

    public void setExecutionStack(MyIStack<IStatement> executionStack) {
        this.executionStack = executionStack;
    }

    public MyIDictionary<String, BufferedReader> getFileTable() {
        return fileTable;
    }
    public void setFileTable(MyIDictionary<String, BufferedReader> newFileTable) {
        this.fileTable = newFileTable;
    }
    public MyIDictionary<String, Value> getSymbolTable() {
        return symbolTable;

    }

    public void setSymbolTable(MyIDictionary<String, Value> symbolTable) {
        this.symbolTable = symbolTable;
    }

    public void setHeap(MyIHeap newHeap) {
        this.heap = newHeap;
    }

    public MyIList<Value> getOutputList() {
        return outputList;
    }

    public void setOutputList(MyIList<Value> outputList) {
        this.outputList = outputList;
    }

    public IStatement getOriginalProgram() {
        return originalProgram;
    }

    public void setOriginalProgram(IStatement originalProgram) {
        this.originalProgram = originalProgram;
    }

    public void addOut(Value number) {
        this.outputList.add(number);
    }

    public boolean isNotCompleted() {
        return executionStack.isEmpty();
    }

    public ProgramState oneStep() throws ToyLanguageInterpreterException {
        if (executionStack.isEmpty())
            throw new ADTEmptyException("Stack empty");
        IStatement currentStatement = executionStack.pop();
        return currentStatement.execute(this);
    }

    public MyIHeap getHeap() {
        return heap;
    }



    public String exeStackToString() {
        StringBuilder exeStackStringBuilder = new StringBuilder();
        List<IStatement> stack = executionStack.getReversed();
        for (IStatement statement : stack) {
            exeStackStringBuilder.append(statement.toString()).append("\n");
        }
        return exeStackStringBuilder.toString();
    }

    public String symbolTableToString() throws ToyLanguageInterpreterException {
        StringBuilder symbolTableStringBuilder = new StringBuilder();

        for (String key : symbolTable.keySet()) {
            symbolTableStringBuilder.append(String.format("%s -> %s\n", key, symbolTable.get(key).toString()));
        }
        return symbolTableStringBuilder.toString();
    }

    public String outputToString() {
        StringBuilder outStringBuilder = new StringBuilder();

        for (Value elem : outputList.getList()) {
            outStringBuilder.append(String.format("%s\n", elem.toString()));
        }
        return outStringBuilder.toString();
    }

    public String fileTableToString() {
        StringBuilder fileTableStringBuilder = new StringBuilder();
        for (String key : fileTable.keySet()) {
            fileTableStringBuilder.append(String.format("%s\n", key));
        }
        return fileTableStringBuilder.toString();
    }

    public String heapToString() throws ToyLanguageInterpreterException {
        StringBuilder heapStringBuilder = new StringBuilder();
        for (int key: heap.keySet()) {
            heapStringBuilder.append(String.format("%d -> %s\n", key, heap.get(key)));
        }
        return heapStringBuilder.toString();
    }
    @Override
    public String toString() {
        return "ID: "+ id+ "\nExecution stack: \n" + executionStack.getReversed() + "\nSymbol table: \n" + symbolTable.toString() + "\nOutput list: \n" + outputList.toString()+"\n"+"FileTable: "+fileTable.toString()+"\n"+"Heap:"+heap.toString()+"\n";
    }

    public String programStateToString() throws ToyLanguageInterpreterException {
        return "ID: "+ id+ "\nExecution stack: \n" + exeStackToString() + "Symbol table: \n" + symbolTableToString() + "Output list: \n" + outputToString()+"FileTable: " +fileTableToString()+"\n"+ "Heap:" +heapToString()+"\n";
    }


}
