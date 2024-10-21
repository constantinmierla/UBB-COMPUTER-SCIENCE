package repository;

import domain.Entity;
import domain.validators.Validator;

import java.io.*;
import java.util.*;
public abstract class AbstractFileRepository <ID, E extends Entity<ID>> extends InMemoryRepository<ID, E> {
    String filename;

    public AbstractFileRepository(String filename, Validator<E> validator) {
        super(validator);
        this.filename = filename;
        loadData();
    }

    private void loadData(){
        try(BufferedReader reader = new BufferedReader(new FileReader(filename))){
            String newLine;
            while((newLine = reader.readLine()) != null){
                System.out.println(newLine);
                List<String> data = Arrays.asList(newLine.split(";"));
                E entity = extractEntity(data);
                super.save(entity);
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public abstract E extractEntity(List<String> attributes);

    protected abstract String createEntityAsString(E entity);

    @Override
    public E save(E entity){
        E result = super.save(entity);
        if(result == null)
            writeToFile(entity);
        return entity;
    }

    protected void writeToFile(E entity){
        try(BufferedWriter writer = new BufferedWriter(new FileWriter(filename, true))){
            writer.write(createEntityAsString(entity));
            writer.newLine();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
