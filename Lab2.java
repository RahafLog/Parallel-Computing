
package lab2_parrall;

import java.util.concurrent.*;

public class Lab2_parrall {

    public static void main(String[] args) {
       //difined varibals 
      
       //we use this if I want to know how many threads my device can create  
//       final int Thread_Count = Runtime.getRuntime().availableProcessors();
//       System.out.println(Thread_Count);

       //The user determines how many threads want to use 
          final int Thread_Count = 2;
          
          int [] x = {1,2,3,4,5,6};
          int [] y = {10,20,30,40,50,60};
          int [] z = new int [x.length];
          
       //difined threads 
       ExecutorService ex = Executors.newCachedThreadPool(); //no difine number 
       ex.execute(new VictorAddition(Thread_Count,0,x,y,z));
       ex.execute(new VictorAddition(Thread_Count,1,x,y,z)); //send th num and rank and matrix
//       Thread th0 = new Thread(new VictorAddition(Thread_Count,0,x,y,z));
//       Thread th1 = new Thread(new VictorAddition(Thread_Count,1,x,y,z)); //not pool
       
       //start threas 
       ex.shutdown();
       while(!ex.isTerminated()){
           
       }
//       th0.start();
//       th1.start();
       
       //print the result 
       System.out.println("x[] ");
       for(int i =0 ; i< x.length; i++){
           System.out.println(x[i]);
            
       }
       System.out.println("***********************");
       System.out.println("y[] ");
              for(int i =0 ; i< y.length; i++){
           System.out.println(y[i]);
            
       }
                System.out.println("***********************");
                System.out.println("z[] ");
                     for(int i =0 ; i< z.length; i++){
           System.out.println(z[i]);
            
       }
        

    }
    
}

//difine class task 

class VictorAddition implements Runnable {
    int Thread_Count;
    int rank ;
    int[] victorx;
    int[] victory;
    int[] victorz;
    
    public VictorAddition (int Thread_Count,int rank ,int[] x,int[] y,int[] z){
    this.Thread_Count = Thread_Count;
    this.rank = rank;
    this.victorx = x;
    this.victory = y;
    this.victorz = z;
        
    }
    
    public void run(){
        int my_m = victorx.length / Thread_Count; //كانو تقسيم التاسكات ع الثريدات
        int my_firstRow = rank * my_m;
        int my_lastRow = my_firstRow + my_m;
        
        for(int i =my_firstRow; i<my_lastRow ; i++){
            victorz[i] = victorx[i]+victory[i];
            System.out.println("thread Rank = "+this.rank+" , the value victor"+"["+i+"]"+victorz[i]);
        }
    }
    
}