package Collection.Dictionary;

import Model.Exception.ToyLanguageInterpreterException;

import java.util.Collection;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class MyDictionary<K,V> implements MyIDictionary<K,V>{
    private HashMap<K,V> dict;

    public MyDictionary(){
        dict = new HashMap<K,V>();
    }

    @Override
    public V get(K key) throws ToyLanguageInterpreterException {
        if(!containsKey(key))
            throw new ToyLanguageInterpreterException(key+" is not defined");
        return this.dict.get(key);
    }

    @Override
    public K getKey(V value){
        for (K key: dict.keySet()){
            if (dict.get(key).equals(value))
                return key;
        }
        return null;
    }

    @Override
    public V put(K key, V value) throws ToyLanguageInterpreterException {
//        if(!containsKey(key))
//            throw new ToyLanguageInterpreterException(key+" is not defined");
        return this.dict.put(key,value);

    }

    @Override
    public int size(){
        return dict.size();
    }

    @Override
    public boolean containsKey(K key){
        return dict.containsKey(key);
    }

    @Override
    public boolean containsValue(V value){
        return dict.containsValue(value);
    }


    public void remove(K key) throws ToyLanguageInterpreterException {
        if(!containsKey(key))
            throw new ToyLanguageInterpreterException(key+" is not defined");
        this.dict.remove(key);    }

    @Override
    public Collection<V> values(){
        return dict.values();
    }

    @Override
    public Set<K> keySet(){
        return dict.keySet();
    }


    public Map<K,V> getContent()
    {
        return dict;
    }

    @Override
    public void setContent(Set<Map.Entry<K,V>> set) throws ToyLanguageInterpreterException {
        dict.clear();
        for (Map.Entry<K,V> entry : set){
            this.put(entry.getKey(), entry.getValue());
        }
    }

    @Override
    public Set<Map.Entry<K,V>> entrySet(){
        return dict.entrySet();
    }

    @Override
    public MyIDictionary<K, V> clone_dict() throws ToyLanguageInterpreterException {
        MyIDictionary<K, V> di = new MyDictionary<>();
        for(K key : this.keySet())
            di.put(key, dict.get(key));
        return di;
    }


    @Override
    public String toString(){
        return dict.toString();
    }



}
