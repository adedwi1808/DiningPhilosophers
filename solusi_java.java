public class DiningPhilosophersSimulation {

    static class DiningPhilosophers {
        enum State { THINKING, HUNGRY, EATING }
        private final State[] states = new State[5];
        private final Object lock = new Object();

        public DiningPhilosophers() {
            for (int i = 0; i < 5; i++) {
                states[i] = State.THINKING;
            }
        }

        public void takeForks(int id) throws InterruptedException {
            synchronized (lock) {
                states[id] = State.HUNGRY;
                while (!canEat(id)) {
                    lock.wait();
                }
                states[id] = State.EATING;
                System.out.println("🍝 Philosopher " + id + " is eating.");
            }
        }

        public void putForks(int id) {
            synchronized (lock) {
                states[id] = State.THINKING;
                System.out.println("💭 Philosopher " + id + " is thinking.");
                lock.notifyAll();
            }
        }

        private boolean canEat(int id) {
            int left = (id + 4) % 5;
            int right = (id + 1) % 5;
            return states[left] != State.EATING && states[right] != State.EATING;
        }
    }

    static class Philosopher implements Runnable {
        private final int id;
        private final DiningPhilosophers table;

        public Philosopher(int id, DiningPhilosophers table) {
            this.id = id;
            this.table = table;
        }

        @Override
        public void run() {
            try {
                while (true) {
                    System.out.println("💬 Philosopher " + id + " is thinking...");
                    Thread.sleep((long) (Math.random() * 1000));

                    table.takeForks(id);

                    Thread.sleep((long) (Math.random() * 1000)); // makan

                    table.putForks(id);
                }
            } catch (InterruptedException e) {
                System.out.println("Philosopher " + id + " was interrupted.");
            }
        }
    }

    public static void main(String[] args) {
        DiningPhilosophers table = new DiningPhilosophers();

        for (int i = 0; i < 5; i++) {
            new Thread(new Philosopher(i, table)).start();
        }
    }
}
