import mpi.MPI;

public class Main {
    public static void main(String[] args) {
        MPI.Init(args);

        int rank = MPI.COMM_WORLD.Rank();
        int size = MPI.COMM_WORLD.Size();

        //example

//        // Example 1
        Graph graph2 = new Graph(4);
        graph2.addEdge(0, 1);
        graph2.addEdge(1, 2);
        graph2.addEdge(0, 3);

        Colors colors2 = new Colors(2);
        colors2.addColor(0, "pink");
        colors2.addColor(1, "black");

        // Example 2
//        Graph graph2 = new Graph(5);
//        graph2.addEdge(0, 1);
//        graph2.addEdge(1, 2);
//        graph2.addEdge(2, 3);
//        graph2.addEdge(3, 4);
//        graph2.addEdge(4, 0);
//        graph2.addEdge(2, 0);
//        graph2.addEdge(0, 4);
//        graph2.addEdge(4, 3);
//        graph2.addEdge(3, 1);
//
//        Colors colors2 = new Colors(3);
//        colors2.addColor(0, "red");
//        colors2.addColor(1, "green");
//        colors2.addColor(2, "blue");

        // Example 3
//        Graph graph2 = Graph.generateRandomConnectedGraph(10);
//        Colors colors2 = new Colors(5);
//        colors2.addColor(0, "red");
//        colors2.addColor(1, "green");
//        colors2.addColor(2, "blue");
//        colors2.addColor(3, "yellow");
//        colors2.addColor(4, "pink");


        if (rank==0){
            System.out.println("Main process");

            try{
                long start = System.nanoTime();

                System.out.println("Example:");
                System.out.println(graph2);
                System.out.println("Colored Graph:");
                System.out.println(GraphColoring.graphColoringMain(size,graph2,colors2));
                long stop = System.nanoTime();

                long time = stop - start;
                System.out.println("Time: " + time / 1000000 + " ms");
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        else {
            System.out.println("Process rank: "+ rank);

            int colorsNumber = colors2.getColorsNumber();

            GraphColoring.graphColoringChild(rank, size, graph2, colorsNumber);
        }
        MPI.Finalize();

    }
}
