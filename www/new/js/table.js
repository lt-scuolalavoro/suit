Vue.component("suit-table", {
  data() {
    return {
      status: null,
      filter: null,
      sortBy: "name",
      items: [],
      fields: [
        { key: "firstName", sortable: true, label: "First name" },
        { key: "lastName", sortable: true, label: "Last name" },
        { key: "birthDate", label: "Birth date" },
        { key: "salary", sortable: true, label: "Salary" },
        { key: "action", label: "Actions" }
      ],
      modalInfo: { title: "", content: "" }
    };
  },
  methods: {
    showModalInfo(button) {
      this.modalInfo.content = "Hello";
      this.$root.$emit("bv::show::modal", "modalInfo", button);
    },
    showModalDelete(button) {
      this.$root.$emit("bv::show::modal", "modalDelete", button);
    },
    resetModal() {
      this.modalInfo.title = "";
      this.modalInfo.content = "";
    }
  },
  mounted() {
    axios.get("cgi/users.cgi").then(response => (this.items = response.data));
  },
  template: `
  <div>
  <b-row>
    <b-form-group horizontal label="Filter" class="mb-2 ml-4">
        <b-input-group>
        <b-form-input v-model="filter" placeholder="Type to Search" />
        <b-input-group-append>
            <b-btn :disabled="!filter" @click="filter = ''"" ><i class="fas fa-search"></i></b-btn>
        </b-input-group-append>
        </b-input-group>
    </b-form-group>
    <b-form-checkbox id="checkbox1"
                     v-model="status"
                     value="accepted"
                     unchecked-value="not_accepted" class="mt-2 ml-3" >
    Show deleted candidates
    </b-form-checkbox>
</b-row>

     <b-table :sort-by.sync="sortBy"
            striped
            hover
             :items="items"
             :fields="fields">
     <template slot="action" slot-scope="row">
         
         <b-button-group>
            <b-button @click.stop="showModalInfo(this)" title="Show details" variant="outline-primary" size="sm"><i class="fas fa-ellipsis-v"></i></b-button>
            <b-button variant="outline-primary" title="Edit candidate" size="sm"><i class="fas fa-pencil-alt"></i></b-button>
            <b-button @click.stop="showModalDelete()" variant="outline-danger" title="Delete candidate"size="sm"><i class="far fa-trash-alt"></i></b-button>
         </b-button-group>

     </template>
    </b-table>

    <b-modal id="modalInfo" @hide="resetModal" :title="modalInfo.title" ok-only>
      <pre>{{modalInfo.content}}</pre>
    </b-modal>

    <b-modal id="modalDelete" title="Delete candidate">Are you sure?</b-modal>
</div>
    `
});
