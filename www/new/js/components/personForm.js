Vue.component("person-form", {
  props: {
    edit: Boolean
  },
  data() {
    return {
      person: {
        id: 0,
        firstName: "",
        lastName: "",
        birthDate: "",
        employed: "",
        salary: "",
        notes: "",
        contacts: []
      },
      contactName: "",
      contactLink: "",
      idToRemove: 0,
      fields: [
        { key: "name", label: "Name" },
        { key: "link", label: "Link" },
        { key: "action", label: "Action" }
      ],
      date: "date",
      removedContactsID: []
    };
  },
  mounted() {
    if (this.edit) {
      let url = new URL(window.location.href);
      let id = url.searchParams.get("id");
      this.person.id = id;

      axios
        .get("cgi/candidate.cgi", {
          params: {
            id: this.person.id
          }
        })
        .then(response => {
          let data = response.data[0];
          this.person.firstName = data.firstName;
          this.person.lastName = data.lastName;
          this.person.birthDate = data.birthDate;
          this.person.employed = data.employed;
          this.person.salary = data.salary;
          this.person.notes = data.notes;
          this.person.contacts = data.contacts;
        });
    }
  },
  methods: {
    setContact() {
      if (this.contactName != "" && this.contactLink != "") {
        this.person.contacts.push({
          name: this.contactName,
          link: this.contactLink
        });
        if (this.edit) {
          let contact_id = "";
          axios.get("cgi/contacts.cgi").then(response => {
            let len = response.data.length;
            contact_id = parseInt(response.data[len - 1].id) + 1;
            contact_id = contact_id.toString();
            let last = this.person.contacts.length - 1;
            this.person.contacts[last].id = contact_id;
            this.person.contacts[last].candidateId = this.person.id;
          });
        }
        this.contactName = "";
        this.contactLink = "";
      }
    },
    showModalDelete(button, row) {
      this.$root.$emit("bv::show::modal", "modalDelete", button);
      this.idToRemove = row.item.id;
    },
    onSubmitClick() {
      let op = this.edit ? "edit" : "add";

      axios
        .post("cgi/" + op + "Candidate.cgi", {
          id: this.person.id,
          firstName: this.person.firstName,
          lastName: this.person.lastName,
          birthDate: this.person.birthDate,
          employed: this.person.employed,
          salary: this.person.salary,
          notes: this.person.notes,
          contacts: this.person.contacts,
          removed_contacts_ids: this.removedContactsID
        })
        // .then(() => (window.location = "home.html"));
    },
    removeContact() {
      this.removedContactsID.push(this.idToRemove);
      console.log(this.removedContactsID)
      var index = this.person.contacts.indexOf(
        this.person.contacts[this.idToRemove]
      );
      this.person.contacts.splice(index, 1);
    }
  },

  template: `
    <div align = "center">
        <b-form-group horizontal
                      id="formFirstName"
                      label="First name:"
                      label-for="inputFirstName">
            <b-form-input id="inputFirstName"
                          placeholder="insert first name here"
                          v-model="person.firstName">
            </b-form-input>
        </b-form-group>

        <b-form-group horizontal
                      id="formLastName"
                      label="Last name:"
                      label-for="inputLastName">
            <b-form-input id="inputLastName"
                          placeholder="insert last name here"
                          v-model="person.lastName">
            </b-form-input>
        </b-form-group>

        <b-form-group horizontal
                      id="formBirthDate"
                      label="Birth date:"
                      label-for="inputBirthDate">
            <b-form-input id="inputBirthDate"
                          :type = "date"
                          placeholder="insert the birth date here "
                          v-model="person.birthDate">
            </b-form-input>
        </b-form-group>

        <b-form-group horizontal
                      id="formEmployed"
                      label="Employed:"
                      label-for="inputEmployed">
            <b-form-radio-group
                    v-model="person.employed"
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
                          v-model="person.salary">
            </b-form-input>
        </b-form-group>

        <b-form-group horizontal
                      id="formNotes"
                      label="Notes:"
                      label-for="inputNotes">
            <b-form-textarea id="inputNotes"
                      placeholder="insert notes about the candidate here"
                      v-model="person.notes"
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
                              variant = "outline-primary"
                              @click = "setContact()">+</b-button>
                </b-col>
            </b-row>

            <b-table striped
                     :items = "person.contacts"
                     :fields = "fields">

                <template slot="action" slot-scope="row">
                    <b-button-group>
                        <b-button @click.stop="showModalDelete(this, row)" variant="outline-danger" title="Delete contact"size="sm"><i class="far fa-trash-alt"></i></b-button>
                    </b-button-group>
                 </template>
                
            </b-table>

            </b-form-group>

        <div align = "right">
            <b-button variant="outline-danger">Cancel</b-button>
            <b-button @click="onSubmitClick" variant="outline-primary">Submit</b-button>
        </div>

        <b-modal id="modalDelete" @ok="removeContact" title="Delete contact">Are you sure?</b-modal>
    </div>
    `
});

new Vue({
  el: "#form-demo"
});
