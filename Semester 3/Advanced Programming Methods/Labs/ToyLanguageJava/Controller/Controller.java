package Controller;

import Collection.Stack.MyIStack;
import Model.Exception.ToyLanguageInterpreterException;
import Model.State.ProgramState;
import Model.Statement.IStatement;
import Model.Value.RefValue;
import Model.Value.Value;
import Repository.IRepository;

import java.io.IOException;
import java.util.*;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Controller {

    private ExecutorService executorService;
    IRepository repo;

    boolean displayFlag = false;


    public IRepository getRepo(){return this.repo;}
    public void setDisplayFlag(boolean value){
        this.displayFlag=value;
    }
    public Controller(IRepository rep){
        this.repo=rep;
    }

    //for a5 mobed to prg state
    /*public ProgramState oneStep(ProgramState state) throws ToyLanguageInterpreterException {
        MyIStack<IStatement> stack = state.getExecutionStack();
        if (stack.isEmpty()){
            throw new ToyLanguageInterpreterException("Program state stack is empty.");
        }
        IStatement currentStatement = stack.pop();
        state.setExecutionStack(stack);
        return currentStatement.execute(state);

    }*/

    public List<ProgramState> removeCompletedProgram(List<ProgramState> inPrgList){
        return inPrgList.stream().
                filter(p->!p.isNotCompleted())
                .collect(Collectors.toList());
    }



    public Map<Integer,Value> safeGarbageCollector(List<Integer> symTableAddr, List<Integer> heapAddr, Map<Integer, Value> heap)
    {
        return heap.entrySet().stream()
                .filter(e -> ( symTableAddr.contains(e.getKey()) || heapAddr.contains(e.getKey())))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    public void conservativeGarbageCollector(List<ProgramState> programStates) {
        List<Integer> symTableAddresses = Objects.requireNonNull(programStates.stream()
                        .map(p -> getAddrFromSymTable(p.getSymbolTable().values()))
                        .map(Collection::stream)
                        .reduce(Stream::concat).orElse(null))
                .collect(Collectors.toList());
        programStates.forEach(p -> {
            p.getHeap().setContent((HashMap<Integer, Value>) safeGarbageCollector(symTableAddresses, getAddrFromHeap(p.getHeap().getContent().values()), p.getHeap().getContent()));
        });
    }

    public List<Integer> getAddrFromHeap(Collection<Value> heapValues) {
        return heapValues.stream()
                .filter(v->v instanceof RefValue)
                .map(v->{RefValue v1=(RefValue) v;return v1.getAddress();})
                .collect(Collectors.toList());
    }
    public List<Integer> getAddrFromSymTable(Collection<Value> symTableValues)
    {
        return symTableValues.stream()
                .filter(v-> v instanceof RefValue)
                .map(v-> {RefValue v1 = (RefValue)v; return v1.getAddress();})
                .collect(Collectors.toList());
    }

    public void oneStepForAllPrograms(List<ProgramState> programStates) throws ToyLanguageInterpreterException,InterruptedException, IOException{

        programStates.forEach(programState -> {
            try {
                this.repo.logPrgStateExec(programState);

            } catch (IOException | ToyLanguageInterpreterException e) {
                System.out.println(e.getMessage());
            }
        });


        List<Callable<ProgramState>> callList = programStates.stream()
                .map((ProgramState p) -> (Callable<ProgramState>) (p::oneStep))
                .collect(Collectors.toList());
        try {
            List<ProgramState> newProgramList = executorService.invokeAll(callList).stream()
                    .map(future -> {
                        try {
                            return future.get();
                        } catch (ExecutionException | InterruptedException e) {
                            System.out.println(e.getMessage());
                        }
                        return null;
                    })
                    //.distinct()
                    .filter(Objects::nonNull).toList();

            programStates.addAll(newProgramList);
        } catch (InterruptedException e)
        {
            throw new ToyLanguageInterpreterException(e.getMessage());
        }

        programStates.forEach(programState -> {
            try {
                this.repo.logPrgStateExec(programState);

            } catch (IOException | ToyLanguageInterpreterException e) {
                System.out.println(e.getMessage());
            }
        });

        this.repo.setProgramStates(programStates);
    }

    public void allStep() throws InterruptedException,ToyLanguageInterpreterException, IOException {
        this.executorService = Executors.newFixedThreadPool(2);  // maximum 2 threads concurrently

        List<ProgramState> programStates = removeCompletedProgram(this.repo.getProgramList());

        while (programStates.size() > 0) {

            conservativeGarbageCollector(programStates);
            oneStepForAllPrograms(programStates);

            programStates = removeCompletedProgram(repo.getProgramList());
        }
        executorService.shutdownNow();
        repo.setProgramStates(programStates);
    }

    private void display(ProgramState prg)
    {
        if(displayFlag)
            System.out.println(prg.toString());

    }

    /*public void allSteps() throws ToyLanguageInterpreterException, IOException {
        ProgramState program = this.repo.getCurrentState();
        this.repo.logPrgStateExec();
        display();
        while(!program.getExecutionStack().isEmpty()){
            oneStep(program);
            this.repo.logPrgStateExec();
            display();

            program.getHeap().setContent(
                    (HashMap<Integer, Value>) unsafeGarbageCollector(getAddrFromSymTable(program.getSymbolTable().values()),
                                    program.getHeap().getContent(),getAddrFromHeap(program.getHeap().getContent().values())));
            this.repo.logPrgStateExec();
            display();
        }
    }*/

    /*private void display(){
        if (displayFlag) {
            System.out.println(this.repo.getCurrentState().toString());;
        }
        ProgramState program = this.repo.getCurrentState();
        if (program.getExecutionStack().size()==0 && !(displayFlag)){
            System.out.println(this.repo.getCurrentState().toString());
        }
    }*/
}
