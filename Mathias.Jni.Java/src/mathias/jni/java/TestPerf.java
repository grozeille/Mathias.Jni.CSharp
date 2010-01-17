package mathias.jni.java;

public class TestPerf {

    /**
     * @param args
     */
    public static void main(String[] args) {
        long begin = System.currentTimeMillis();
        String mathias = "mathias";
        
        for(int i=0; i < 100000; i++)
        {
            MyJavaClass obj = new MyJavaClass();
            obj.setPeople(mathias);
            obj.sayHello();
        }
        
        long end = System.currentTimeMillis();
        
        System.out.println(String.format("total time: %dms", end-begin));
    }

}
