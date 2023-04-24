package View;

import Collection.Dictionary.MyDictionary;
import Controller.Controller;
import Model.Exception.ADTEmptyException;
import Model.Exception.StatementExecutionException;
import Model.Exception.ToyLanguageInterpreterException;
import Model.Type.Type;

import java.io.IOException;
import java.util.Objects;
import java.util.Scanner;

public class RunExampleCommand extends Command{

    private final Controller controller;

    public RunExampleCommand(String key, String description, Controller controller){
        super(key,description);
        this.controller=controller;
    }

    @Override
    public void execute() throws InterruptedException {
        try {
            System.out.println("Do you want to display the steps?[y/n]");
            Scanner readOption = new Scanner(System.in);
            String option = readOption.next();
            controller.setDisplayFlag(Objects.equals(option, "Y"));
            this.controller.getRepo().getProgramList().get(0).getExecutionStack().getValues().get(0).typeCheck(new MyDictionary<String, Type>());
            controller.allStep();
        } catch (ToyLanguageInterpreterException | IOException exception) {
            System.out.println(exception.getMessage());
        }
    }
}
