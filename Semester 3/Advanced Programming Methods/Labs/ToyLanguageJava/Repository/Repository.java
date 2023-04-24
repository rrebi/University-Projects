package Repository;

import Model.Exception.ToyLanguageInterpreterException;
import Model.State.ProgramState;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

public class Repository implements IRepository{

    private  List<ProgramState> programStates;
    private final String logFilePath;
    private int currentPosition;

    public Repository(ProgramState programState, String logFilePath){
        this.logFilePath = logFilePath;
        this.programStates = new ArrayList<>();
        this.currentPosition = 0;
        this.addProgram(programState);
    }



    public int getCurrentPosition() {
        return currentPosition;
    }

    public void setCurrentPosition(int currentPosition){
        this.currentPosition=currentPosition;
    }

    @Override
    public List<ProgramState> getProgramList(){
        return this.programStates;
    }

    @Override
    public void setProgramStates(List<ProgramState> programStates){
        this.programStates=programStates;
    }

    @Override
    public void addProgram(ProgramState program){
        this.programStates.add(program);
    }

    @Override
    public ProgramState getCurrentState(){
        return this.programStates.get(this.currentPosition);
    }

    @Override
    public void logPrgStateExec(ProgramState p) throws ToyLanguageInterpreterException, IOException {
        PrintWriter logFile;
        logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath, true)));
        logFile.println(p.programStateToString());
        logFile.close();
    }

    @Override
    public void emptyLogFile() throws ToyLanguageInterpreterException, IOException {
        PrintWriter logFile;
        logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath,false)));
        logFile.close();
    }
}
