Vue.component("person-form", {
    data(){
        return {
            firstName: '',
            lastName: '',
            birthDate: '',
            employed: '',
            salary: '',
            notes: '',
            contacts: [],
            contactName: '',
            contactLink: '',
            fields: [
                {key: "name", label: "Name"},
                {key: "link", label: "Link"},
                {key: "action", label: "Action"}
            ],
            date: 'date'
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
        },
        setNotes(value) {
            this.notes = value;
        },
        setContact(){
            if(this.contactName != '' && this.contactLink != ''){
                this.contacts.push({name: this.contactName, link: this.contactLink});
                this.contactName = '';
                this.contactLink = '';
            }
        },
        showModalDelete(button){
            this.$root.$emit("bv::show::modal", "modalDelete", button);
        },
    },

    template:`
    <div align = "center">
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
                          :type = "date"
                          placeholder="insert the birth date here "
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

        <b-form-group horizontal
                      id="formNotes"
                      label="Notes:"
                      label-for="inputNotes">
            <b-form-textarea id="inputNotes"
                      placeholder="insert notes about the candidate here"
                      v-model="notes"
                      @input="setNotes(notes)"
                      :rows="3"
                      no-resize>
            </b-form-textarea>
        </b-form-group>

        <b-form-group horizontal
                      id = "formContacts"
                      label = "Contacts:"
                      label-for = "inputContactName">
            <b-row>
                <b-col cols = "3">
                    <b-form-input id="inputContactName"
                                  placeholder="name (ex: Gmail)"
                                  v-model="contactName">
                    </b-form-input>
                </b-col>
                <b-col cols = "8">
                    <b-form-input id="inputContactLink"
                                  placeholder="link (ex: mariorossi@gmail.com)"
                                  v-model="contactLink">
                    </b-form-input>
                </b-col>
                <b-col cols = "1">
                    <b-button id = "ContactsButton"
                              variant="outline-primary"
                              @click="setContact()">+</b-button>
                </b-col>
            </b-row>

            <b-table striped
                     :items = "contacts"
                     :fields = "fields">

                <template slot="action" slot-scope="row">
                    <b-button-group>
                        <b-button @click.stop="showModalDelete()" variant="outline-danger" title="Delete contact"size="sm"><i class="far fa-trash-alt"></i></b-button>
                    </b-button-group>
                 </template>
                
            </b-table>

            </b-form-group>

        <div align = "right">
            <b-button variant="outline-danger">Cancel</b-button>
            <b-button variant="outline-primary">Submit</b-button>
        </div>

        <b-modal id="modalDelete" title="Delete contact">Are you sure?</b-modal>
    </div>
    `
});

new Vue({ 
    el: '#form-demo',
 })