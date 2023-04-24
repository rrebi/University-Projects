package View;

import Collection.Dictionary.MyDictionary;
import Collection.Dictionary.MyIDictionary;
import Collection.Heap.MyHeap;
import Collection.Heap.MyIHeap;
import Collection.List.MyIList;
import Collection.List.MyList;
import Collection.Stack.MyIStack;
import Collection.Stack.MyStack;
import Model.Exception.ToyLanguageInterpreterException;
import Model.Expression.*;
import Model.State.ProgramState;
import Model.Statement.*;
import Model.Type.IntType;
import Model.Value.BooleanValue;
import Model.Value.IntValue;
import Model.Value.Value;
import Repository.IRepository;
import Repository.Repository;

import Controller.Controller;
import Model.Type.BooleanType;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.Objects;
import java.util.Scanner;

public class View {

    public void start(){
        boolean ok = false;
        while(!ok){
            try{
                showMenu();
                Scanner readOption = new Scanner(System.in);
                int opt = readOption.nextInt();
                if (opt == 0){
                    ok = true;
                }
                else if (opt == 1){
                    Program1();
                }
                else if (opt == 2){
                    Program2();
                }
                else if (opt == 3){
                    Program3();
                }
                else{
                    System.out.println("Invalid option!");
                }
            }
            catch (Exception ex){
                System.out.println(ex.getMessage());
            }
        }
    }

    private void showMenu(){
        System.out.println("0.Exit");
        System.out.println("1.Run the first program:\n\tint v;\n\tv=2;\n\tPrint(v)");
        System.out.println("2.Run the second program:\nint 1;\n\t a = 2+3*5;\n\t int b;\n\t b=a+1;\n\t Print(b);\n");
        System.out.println("3.Run the third program.\n\t bool a;\n\t a=false;\n\t int v;\n\t If a Then v=2 Else v=3;\n\t Print(v)\n");
        System.out.println("Enter a value:");
    }

    private void Program1() throws ToyLanguageInterpreterException, IOException {
        IStatement ex1=new CompoundStatement(new VariableDeclarationStatement("v",new IntType()),new CompoundStatement(new AssignStatement("v",new ValueExpression(new IntValue(2))),
                new PrintStatement(new VariableExpression("v"))));
        run(ex1);

    }
    private void Program2() throws ToyLanguageInterpreterException, IOException {
        IStatement ex2 = new CompoundStatement(new VariableDeclarationStatement("a", new IntType()),
                new CompoundStatement(new VariableDeclarationStatement("b", new IntType()),
                        new CompoundStatement(new AssignStatement("a", new ArithmeticExpression('+', new ValueExpression(new IntValue(2)),
                                new ArithmeticExpression('*', new ValueExpression(new IntValue(3)), new ValueExpression(new IntValue(5))))),
                                new CompoundStatement(new AssignStatement("b", new ArithmeticExpression('+', new VariableExpression("a"),
                                        new ValueExpression(new IntValue(1)))), new PrintStatement(new VariableExpression("b"))))));
        run(ex2);

    }

    private void Program3() throws ToyLanguageInterpreterException, IOException {
        IStatement ex3 = new CompoundStatement(new VariableDeclarationStatement("a", new BooleanType()),
                new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                        new CompoundStatement(new AssignStatement("a", new ValueExpression(new BooleanValue(true))),
                                new CompoundStatement(new IfStatement(new VariableExpression("a"), new AssignStatement("v", new ValueExpression(
                                        new IntValue(2))), new AssignStatement("v", new ValueExpression(new IntValue(3)))),
                                        new PrintStatement(new VariableExpression("v"))))));
        run(ex3);
    }

    private void run (IStatement e) throws ToyLanguageInterpreterException, IOException {
        MyIStack<IStatement> executionStack = new MyStack<>();
        MyIDictionary<String, Value> symbolTable = new MyDictionary<>();
        MyIList<Value> output = new MyList<>();
        MyIDictionary<String, BufferedReader> fileTable = new MyDictionary<>();

        MyIHeap heap=new MyHeap();


        ProgramState state = new ProgramState(executionStack, symbolTable, output,fileTable, heap, e);


        IRepository repository = new Repository(state, "log.txt");
        Controller controller = new Controller(repository);

        System.out.println("Do you want to see every step? T for true F for false");
        Scanner readOption = new Scanner(System.in);
        String opt = readOption.next();
        controller.setDisplayFlag(Objects.equals(opt,"T"));
        //controller.allSteps();

    }
}
