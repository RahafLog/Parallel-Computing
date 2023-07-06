
package lab3_2_computing;
import java.util.concurrent.locks.*;


public class Lab3_2_computing {
static final int Thread_Count = Runtime.getRuntime().availableProcessors();
static String [] messages = new String [Thread_Count ];
static Lock locks = new ReentrantLock();
static Condition [] notEmpty = new Condition[Thread_Count ];

    public static void main(String[] args) {
         for (int i  = 0 ; i < notEmpty.length ; i++){
             notEmpty[i] = locks.newCondition();
         }
        for (int th = 0 ; th < Thread_Count ; th++){
            new Thread(new send_Recive(th)).start();
        }
        // TODO code application logic here
    }
    static class send_Recive implements Runnable {
        int rank ; 
        public send_Recive(int rank ){
            this.rank = rank ;
        }
        @Override
        public void run(){
            int dest = (rank +1)%Thread_Count;
            String message = "Hello to "+ dest+" from "+ rank ;
            messages[dest] = message;
           
            locks.lock();
            try{
            notEmpty[dest].signal();
            if(messages[rank]== null){
                System.out.println("thread "+ rank+ ": waiting for message ");
                notEmpty[rank].await();
            }
            
        }catch(InterruptedException ex){
            ex.printStackTrace();
        }finally{
                locks.unlock();
            }
            System.out.println("thread"+ rank +" : "+messages[rank]);
        }
        
    }
}
