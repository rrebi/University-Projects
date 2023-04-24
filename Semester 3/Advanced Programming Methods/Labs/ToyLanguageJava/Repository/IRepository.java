package Repository;

import Model.Exception.ToyLanguageInterpreterException;
import Model.State.ProgramState;

import java.io.IOException;
import java.util.List;

public interface IRepository {
    List<ProgramState> getProgramList();

    void setProgramStates(List<ProgramState> programStates);

    ProgramState getCurrentState();

    void addProgram(ProgramState program);

    //void logPrgStateExec() throws ToyLanguageInterpreterException, IOException;

    void logPrgStateExec(ProgramState p) throws ToyLanguageInterpreterException, IOException;

    void emptyLogFile() throws ToyLanguageInterpreterException, IOException;
}
