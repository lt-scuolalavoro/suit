Vue.component("person-form", {
    data(){
        return {
            firstName: '',
            lastName: '',
            birthDate: '',
            employed: '',
            salary: ''
        };
    },

    methods: {
        setFirstName(value) {
            this.firstName = value;
        },
        setLastName(value) {
            this.lastName = value;
        },
        setBirthDate(value) {
            this.birthDate = value;
        },
        setEmployed(value) {
            this.employed = value;
        },
        setSalary(value) {
            this.salary = value;
        }
    },

    template:`
    <div>
        <b-form-group horizontal
                      id="formFirstName"
                      label="First name:"
                      label-for="inputFirstName">
            <b-form-input id="inputFirstName"
                          placeholder="insert first name here"
                          v-model="firstName"
                          @input="setFirstName(firstName)">
            </b-form-input>
        </b-form-group>

        <b-form-group horizontal
                      id="formLastName"
                      label="Last name:"
                      label-for="inputLastName">
            <b-form-input id="inputLastName"
                          placeholder="insert last name here"
                          v-model="lastName"
                          @input="setLastName(lastName)">
            </b-form-input>
        </b-form-group>

        <b-form-group horizontal
                      id="formBirthDate"
                      label="Birth date:"
                      label-for="inputBirthDate">
            <b-form-input id="inputBirthDate"
                          placeholder="insert the birth date here (yyyy-mm-dd)"
                          v-model="birthDate"
                          @input="setBirthDate(birthDate)">
            </b-form-input>
        </b-form-group>

        <b-form-group horizontal
                      id="formEmployed"
                      label="Employed:"
                      label-for="inputEmployed">
            <b-form-radio-group
                    v-model="employed"
                    @input="setEmployed(employed)"
                    id="inputEmployed">
                <b-form-radio value="1">Yes</b-form-radio>
                <b-form-radio value="0">No</b-form-radio>
            </b-form-radio-group>
        </b-form-group>

         <b-form-group horizontal
                      id="formSalary"
                      label="Salary:"
                      label-for="inputSalaty">
            <b-form-input id="inputSalary"
                          placeholder="insert salary here"
                          v-model="salary"
                          @input="setSalary(salary)">
            </b-form-input>
        </b-form-group>
    </div>
    `
});

new Vue({ 
    el: '#form-demo',
 })