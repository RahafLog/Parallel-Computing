
package lab3_computing;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 *
 * @author Rahaf
 */
public class Lab3_computing {
 static final int Thread_Count = Runtime.getRuntime().availableProcessors();
 static final int n = 1000000;
  static double sum = 0.0;
       public static void main(String[] args) {
 
       ExecutorService ex = Executors.newCachedThreadPool();
       long startTime = System.currentTimeMillis();
       
       for (int i = 0 ; i<Thread_Count ; i++){
           ex.execute(new Sum(i));
       }
       
       //start threas 
       ex.shutdown();
       while(!ex.isTerminated()){
           
       }
       long endTime = System.currentTimeMillis();
//       th0.start();
//       th1.start();
       
     System.out.println((sum +1));
     System.out.println("number of thread "+Thread_Count);
     System.out.println("time with "+(endTime -startTime )+ " mills");    

    }
       static class Sum implements Runnable{
           int thread_Rank ;
           Sum(int thread_Rank ){
               this.thread_Rank = thread_Rank;
           }
           public void run(){
          threadSum(thread_Rank);
       }
           void threadSum (int rank){
           double factor ;
           int my_n = n /Thread_Count;
           int my_first = my_n *thread_Rank;
           int my_last = my_first +my_n ;
           double my_sum = 0.0; 
           
           if (my_first % 2==0){
               factor = 1.0;
           }else {
               factor = -1.0 ;
           }
           for(int i = my_first ; i<my_last ; i++){
               sum += factor /(2*i + 1);
               factor = -factor ;
           }
           synchronized (this){
               sum+=my_sum;
           }
          
           }
       }
}
