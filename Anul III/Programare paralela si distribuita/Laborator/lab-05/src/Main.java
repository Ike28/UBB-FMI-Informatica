import java.io.*;
import java.util.*;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main {
    public static void runSequential(File[] files) throws IOException {
        ThreadSafeListManager listManager = new ThreadSafeListManager(
                new ThreadSafeLinkedList<>(),
                Collections.synchronizedSet(new HashSet<>())
        );
        for (File file : files) {
            try(BufferedReader bufferedReader = new BufferedReader(new FileReader(file))){
                String line;
                while ((line = bufferedReader.readLine()) != null) {
                    Participant participant = Participant.fromString(line, file);
                    listManager.processParticipant(participant);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
//        System.out.println(lst.getJavaLinkedList().size());
//        for(Participant p : lst.getJavaLinkedList()){
//            System.out.println(p);
//        }
        listManager.sortList();
        writeToFile(listManager.getLst(), "sequentialResult.txt");
    }

    public static void writeToFile(ThreadSafeLinkedList<Participant> lst, String filename) throws IOException{
        try (FileWriter fileWriter = new FileWriter(filename)) {
            Node<Participant> current = lst.getHead();
            while (current.getNext() != null) {
                Participant p = current.getData();
                fileWriter.write(p.getId() + " " + p.getScore() + "\n");
                current = current.getNext();
            }
        }
    }

    public static boolean checkEq(String fileName1, String fileName2){

        try {
            File file1 = new File(fileName1);
            File file2 = new File(fileName2);

            if(file1.length() != file2.length())
                return false;

            Scanner f1scanner = new Scanner(file1);
            Scanner f2scanner = new Scanner(file2);

            while(f1scanner.hasNextInt())
                if(f1scanner.nextInt() != f2scanner.nextInt()) {
                    return false;
                }

            f1scanner.close();
            f2scanner.close();

            return true;
        }
        catch(IOException exception){
            exception.printStackTrace();
        }
        return false;
    }

    public static void runParallel(File[] files, int numberOfThreads, int numberOfProducers) throws InterruptedException, IOException {
        CheckClass counter = new CheckClass(files.length);
        CyclicBarrier barrier = new CyclicBarrier(numberOfProducers);
        CyclicBarrier barrierForAll = new CyclicBarrier(numberOfThreads);
        ThreadSafeQueue<Participant> queue = new ThreadSafeQueue<>(new LinkedList<>(), 50);
        ThreadSafeLinkedList<Participant> lst = new ThreadSafeLinkedList<>();

        ExecutorService exec = Executors.newFixedThreadPool(numberOfProducers);
        for (int i = 0; i < files.length; i++) {
            Runnable task = new Producer(queue, files[i], i, lst, counter, barrier, barrierForAll);
            exec.execute(task);
        }

        Consumer[] consumers = new Consumer[numberOfThreads - numberOfProducers];

        Set<Participant> synchronizedBlackListSet = Collections.synchronizedSet(new HashSet<>());

        for(int i = 0; i < numberOfThreads - numberOfProducers; i++) {
            consumers[i] = new Consumer(queue, lst, synchronizedBlackListSet, counter, barrierForAll);
            consumers[i].start();
        }

        exec.shutdown();

        for(int i = 0; i < numberOfThreads - numberOfProducers; i++){
            consumers[i].join();
        }

        lst.sort();
        writeToFile(lst, "parallelResult.txt");
    }

    public static void main(String[] args) throws Exception {
        File[] files = new File(args[0]).listFiles();
        assert files != null;
        int numberOfThreads = Integer.parseInt(args[1]);
        Long time1, time2;
        if (numberOfThreads == 1) {
            time1 = System.nanoTime();
            runSequential(files);
            time2 = System.nanoTime();
            System.out.println(Utils.timeDiff(time1, time2));
            return;
        }

        int numberOfProducers = Integer.parseInt(args[2]);
        time1 = System.nanoTime();
        runParallel(files, numberOfThreads, numberOfProducers);
        time2 = System.nanoTime();
        System.out.println(checkEq("sequentialResult.txt", "parallelResult.txt"));
        System.out.println(Utils.timeDiff(time1, time2));
    }
}