package mathias.jni.java;

/**
 * ma class d'exemple
 * @author Mathias
 */
public class MyJavaClass {
    private String people;

    public String getPeople() {
        return this.people;
    }

    public void setPeople(String people) {
        this.people = people;
    }
    
    public String sayHello()
    {
        return String.format("Hello %s from Java!", this.people);
    }
}
