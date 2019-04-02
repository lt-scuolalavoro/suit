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
        contacts: [],
      },
      valid: [false, false, false, false, false, true, true, true],
      state: false,
      contactName: "",
      stringSalary: "Insert salary here",
      contactLink: "",
      idToRemove: 0,
      row_contact_index: 0,
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
          this.check1();
          this.check2();
          this.check3();
          this.check6();
          this.check7();
          this.check8();
          this.check4();
          this.check5();
        });
    }
  },
  methods: {
    setContact() {
      if (this.contactName != "" && this.contactLink != "" && this.valid[6] && this.valid[7]) {
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
      this.row_contact_index = row.index;
    },
    onSubmitClick() {
      this.check5();
      let op = this.edit ? "edit" : "add";
      let ok = true;
      let i=0;
      while (i<8 && ok) {
        ok = this.valid[i];
        i++;
      }
      if (!ok) {
        alert("Missing or incorrect information. Try again.")
      } else {
        while (this.person.firstName.includes(" ")) {
          this.person.firstName = this.person.firstName.replace(" ", "`")
        }
        while (this.person.lastName.includes(" ")) {
          this.person.lastName = this.person.lastName.replace(" ", "`")
        }
        while (this.person.notes.includes(" ")) {
          this.person.notes = this.person.notes.replace(" ", "`")
        }
        for (i=0; i<this.person.contacts.length; i++) {
          while (this.person.contacts[i].name.includes(" ")) {
            this.person.contacts[i].name = this.person.contacts[i].name.replace(" ", "`")
          }
          while (this.person.contacts[i].link.includes(" ")) {
            this.person.contacts[i].link = this.person.contacts[i].link.replace(" ", "`")
          }
        }
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
        .then(() => (window.location = "home.html"));
      }
      
    },
    resetSalary() {
      this.person.salary="";
    },
    check1() {
      this.valid[0] = (!this.person.firstName == '' &&
                      (this.person.firstName.length>=2 && 
                      this.person.firstName.length<=32) && 
                      (/^[a-zA-Z() èéòà'ù]+$/.test(this.person.firstName)));
    },
    check2() {
      this.valid[1] = (!this.person.lastName == '' &&
                      (this.person.lastName.length>=2 && 
                      this.person.lastName.length<=32) && 
                      (/^[a-zA-Z() èéòà'ù]+$/.test(this.person.lastName)));
    },
    check3() {
      this.valid[2] = !this.person.birthDate == "" && ((parseInt(this.person.birthDate.substring(0, 4)))<(new Date().getFullYear()));
    },
    check4() {
      this.valid[3] = !this.person.employed == "";
      if (this.person.employed==0) {
        this.state = true;
        this.valid[4] = true;
        this.resetSalary();
        this.stringSalary="no salary needed";
      } else {
        this.state = false;
        this.valid[4] = false;
        this.stringSalary="insert salary here";
      }
    },
    check5() {
      if (this.person.employed==0 && !this.person.employed=="") {
        this.valid[4] = true;
      } else {
        this.valid[4] = (!isNaN(this.person.salary) && !this.person.salary=="") && this.person.employed != "" && !this.person.salary.includes(" ");
      }
    },
    check6() {
      if (this.person.notes == null || this.person.notes == "NULL") {
        this.person.notes = "";
      }
      this.valid[5] = this.person.notes.length<=255;
    },
    check7() {
      if (this.contactName != "") {
        this.valid[6] = this.contactName.length>=2 && this.contactName.length<=32;
        this.check8();
      } else {
        this.valid[6] = true;
        this.valid[7] = true;
      }
    },
    check8() {
      if (this.valid[6]) {
        this.valid[7] = (!this.contactLink == "" || this.contactName == "") && this.contactLink.length<=255;
      } else {
        this.valid[7] = false;
      }
    },
    removeContact() {
      this.removedContactsID.push(this.idToRemove);
      var index = this.person.contacts.indexOf(
        this.person.contacts[this.row_contact_index]
      );
      this.person.contacts.splice(index, 1);
    },
    goBack() {
      window.location = "home.html";
    }
  },

  template: `
    <div align = "center">
        <b-form-group label-cols-lg="2"	
                      id="formFirstName"
                      label="First name:"
                      label-for="inputFirstName">
            <b-form-input id="inputFirstName"
                          placeholder="insert first name here"
                          v-model="person.firstName"
                          @input="check1();"
                          :state="this.valid[0]">
            </b-form-input>
        </b-form-group>

        <b-form-group label-cols-lg="2"	
                      id="formLastName"
                      label="Last name:"
                      label-for="inputLastName">
            <b-form-input id="inputLastName"
                          placeholder="insert last name here"
                          v-model="person.lastName"
                          @input="check2();"
                          :state="this.valid[1]">
            </b-form-input>
        </b-form-group>

        <b-form-group label-cols-lg="2"	
                      id="formBirthDate"
                      label="Birth date:"
                      label-for="inputBirthDate">
            <b-form-input id="inputBirthDate"
                          :type = "date"
                          placeholder="insert the birth date here "
                          v-model="person.birthDate"
                          @input="check3();"
                          :state="this.valid[2]">
            </b-form-input>
        </b-form-group>

        <b-form-group label-cols-lg="2"	
                      id="formEmployed"
                      label="Employed:"
                      label-for="inputEmployed">
            <b-form-radio-group
                    v-model="person.employed"
                    id="inputEmployed"
                    @input="check4();"
                    :state="this.valid[3]">
                <b-form-radio value="1">Yes</b-form-radio>
                <b-form-radio value="0">No</b-form-radio>
            </b-form-radio-group>
        </b-form-group>

        <b-form-group label-cols-lg="2"	
                      id="formSalary"
                      label="Salary:"
                      label-for="inputSalaty">
            <b-form-input id="inputSalary" :disabled='this.state'
                          :placeholder="this.stringSalary"
                          v-model="person.salary"
                          @input="check5();"
                          :state="this.valid[4]">
            </b-form-input>
        </b-form-group>

        <b-form-group label-cols-lg="2"	
                      id="formNotes"
                      label="Notes:"
                      label-for="inputNotes">
            <b-form-textarea id="inputNotes"
                      placeholder="insert notes about the candidate here"
                      v-model="person.notes"
                      :rows="3"
                      @input="check6();"
                      :state="this.valid[5]"
                      no-resize>
            </b-form-textarea>
        </b-form-group>

        <b-form-group label-cols-lg="2"	
                      id = "formContacts"
                      label = "Contacts:"
                      label-for = "inputContactName">
            <b-row>
                <b-col cols = "3">
                    <b-form-input id="inputContactName"
                                  placeholder="name (ex: Gmail)"
                                  v-model="contactName"
                                  @input="check7();"
                                  :state="this.valid[6]">
                    </b-form-input>
                </b-col>
                <b-col cols = "8">
                    <b-form-input id="inputContactLink"
                                  placeholder="link (ex: mariorossi@gmail.com)"
                                  v-model="contactLink"
                                  @input="check8();"
                                  :state="this.valid[7]">
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
            <b-button @click="goBack();" variant="outline-danger">Cancel</b-button>
            <b-button @click="onSubmitClick" variant="outline-primary">Submit</b-button>
        </div>

        <b-modal id="modalDelete" @ok="removeContact" title="Delete contact">Are you sure?</b-modal>
    </div>
    `
});

new Vue({
  el: "#form-demo"
});
