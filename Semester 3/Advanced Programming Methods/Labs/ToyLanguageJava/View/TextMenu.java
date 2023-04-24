package View;

import Collection.Dictionary.MyDictionary;
import Collection.Dictionary.MyIDictionary;
import Model.Exception.ADTEmptyException;
import Model.Exception.ToyLanguageInterpreterException;

import java.util.Scanner;

public class TextMenu {

    private MyIDictionary<String,Command> commands;

    public TextMenu(){
        this.commands = new MyDictionary<>();
    }

    public void addCommand(Command command) throws ToyLanguageInterpreterException {
        this.commands.put(command.getKey(),command);
    }

    private void printMenu(){
        for (Command command: commands.values()){
            String line = String.format("%4s: %s",command.getKey(),command.getDescription());
            System.out.println(line);;
        }
    }

    public void show(){
        Scanner scanenr = new Scanner(System.in);
        while (true){
            printMenu();;
            System.out.println("Input the option: ");
            String key = scanenr.nextLine();
            try{
                Command command = commands.get(key);
                command.execute();
            }
            catch (ToyLanguageInterpreterException e){
                System.out.println("Invalid option");
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
    }

}
