package com.example.mipt_bank_app;

public class PersonBuilder extends IPersonBuilder{

    @Override
    public PersonBuilder set_first_name(String first_name) {
        first_name_ = first_name;
        return this;
    }

    @Override
    public PersonBuilder set_second_name(String second_name) {
        second_name_ = second_name;
        return this;
    }

    @Override
    public PersonBuilder set_address(String address) {
        address_ = address;
        return this;
    }

    @Override
    public PersonBuilder set_passport_id(String passport_id) {
        passport_id_ = passport_id;
        return this;
    }

    @Override
    public PersonBuilder set_password(String password) {
        password_ = password;
        return this;
    }

    @Override
    public PersonBuilder set_login(String login) {
        login_ = login;
        return this;
    }

    @Override
    public boolean check_args() {
        return first_name_.isEmpty() && second_name_.isEmpty();

    }

    @Override
    public void set_person_first_name() {
        person.set_first_name(first_name_);
    }

    @Override
    public void set_person_second_name() {
        person.set_second_name(second_name_);
    }

    @Override
    public void set_person_passport_id() {
        person.set_passport_id(passport_id_);
    }

    @Override
    public void set_person_address() {
        person.set_address(address_);
    }

    public void set_person_password() {
        person.set_password(password_);
    }

    public void set_person_login() {
        person.set_login(login_);
    }

    @Override
    public Person get_person()   {
        return person;
    }

    @Override
    public void create_person() {
        person = new Person();
    }

    private Person person;
}
