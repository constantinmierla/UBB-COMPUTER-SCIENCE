package domain.validators;

import domain.User;
import java.util.Objects;
public class UserValidator implements Validator<User> {

    @Override
    public void validate(User entity) throws ValidationException {
        String errorMessage = "";

        if (entity.getFirstname().isEmpty()){
            errorMessage += "First name can't be null";
        }
        if (entity.getLastname().isEmpty()){
            errorMessage += "Last name can't be null";
        }
        System.out.println(errorMessage);
        if (!errorMessage.equals("")){
            throw new ValidationException(errorMessage);
        }
    }
}
