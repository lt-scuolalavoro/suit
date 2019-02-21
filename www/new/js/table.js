Vue.component("suit-table", {
  data() {
    return {
      status: null,
      filter: '',
      sortBy: "name",
      items: [],
      filteredItems: [],
      condition:"",
      range1:0,
      range2:0,
      options: [{text: 'Show unemployed candidates', value: 'unemployed'}, 
      {text: 'Show deleted candidates', value: 'deleted'}],
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
    applyFilter(checked) {
      this.condition="";
      if(checked.includes("unemployed")) {
        this.condition+="u";
      }
      if(checked.includes("deleted")) {
        this.condition+="d";
      }
      this.typeSearch();
    },
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
    },
    colorRows(){
      let i
      n = this.items.length
      for(i=0; i<n; i++){
        if(this.items[i].removed=="1"){
          this.items[i]._rowVariant='danger'
        }else{
          if(this.items[i].employed=="1"){
            this.items[i]._rowVariant='success'
          }
        }
      }
    },
    typeSearch(){
      let filteredList=[]
      let i
      let u=1;
      let d=0;
      let r=false;
      let r1=parseInt(this.range1);
      let r2=parseInt(this.range2);
      if (this.condition.includes("u")) {
        u=0;
      }
      if (this.condition.includes("d")) {
        d=1;
      }
      if(r1<r2) {
        this.condition+="r";
        r=true;
      } else {
        this.condition=this.condition.replace('r', '');
      }
      console.log(this.condition);
      for(i=0; i<this.items.length; i++){
        if(this.filter === '') {
            if(this.items[i].employed==u && this.items[i].removed==d) {
              if (r) {
                if (this.items[i].salary>=r1 && this.items[i].salary<=r2) {
                  filteredList.push(this.items[i]);
                  continue;
                }
              } else {
                filteredList.push(this.items[i]);
                continue;
              }
            }
        } else {
          if(this.items[i].lastName.toLowerCase().includes(this.filter.toLowerCase()) || 
          this.items[i].firstName.toLowerCase().includes(this.filter.toLowerCase())){
            if (this.condition!='') {
              if(this.items[i].employed==u && this.items[i].removed==d) {
              if (r) {
                if (this.items[i].salary>=range1 && this.items[i].salary<=range2) {
                  filteredList.push(this.items[i]);
                  continue;
                }
              } else {
                filteredList.push(this.items[i]);
                continue;
              }
            }
            } else {
              filteredList.push(this.items[i]);
            }
          }
        }
      }
      this.filteredItems=filteredList;
    }
  },
  mounted() {
    axios.get("cgi/users.cgi")
    .then(response => {
      this.items = response.data;
      this.colorRows();
    })
  },
  template: `
  <div>
  <b-row>
    <b-form-group horizontal label="Filter" class="mb-2 ml-4">
        <b-input-group>
        <b-form-input @input="typeSearch" v-model="filter" placeholder="Type to Search" />
        <b-input-group-append>
            <b-btn :disabled="!filter" @click="filter = ''"" ><i class="fas fa-search"></i></b-btn>
        </b-input-group-append>
        </b-input-group>
    </b-form-group>
    <div style="padding-left: 1%; padding-top: 3px;">
    <b-button v-b-toggle.collapse1 title="Show filters" size="sm"><i class="fas fa-cog"></i></b-button>
    </div>
    <div style="padding-left: 1%; padding-bottom: 2%; ">
    <b-collapse id="collapse1" class="mt-2">
    <div style="padding-left: -1%; padding-bottom: -2%; padding-top: -3%;">
    <b-card>
    <div>
    <b-form-checkbox-group plain stacked :options="options" id="check" @change="applyFilter">
    <div>
    Min: <b-form-input type="number" @input="typeSearch()" v-model="range1" min="0" size="sm" max="10000"></b-form-input>
    Max: <b-form-input type="number" @input="typeSearch()" v-model="range2" min="0" size="sm" max="10000"></b-form-input>
    </div>
    </b-form-checkbox-group>
    </div>
    </b-card>
    </div>
  </b-collapse>
  </div>
   
</b-row>
     <b-table :sort-by.sync="sortBy"
            striped
            hover
             :items="filter=='' && condition=='' ? items : filteredItems"
             :fields="fields">

     <template slot="action" slot-scope="row">
         
         <b-button-group>
            <b-button variant="outline-primary" size="sm" @click.stop="row.toggleDetails"><i class="fas fa-ellipsis-v"></i></b-button>
            <b-button variant="outline-primary" title="Edit candidate" size="sm"><i class="fas fa-pencil-alt"></i></b-button>
            <b-button @click.stop="showModalDelete()" variant="outline-danger" title="Delete candidate"size="sm"><i class="far fa-trash-alt"></i></b-button>
         </b-button-group>

     </template>
     <template slot="row-details" slot-scope="row">
      <b-card>
        <b-row class="mb-2">
          <b-col sm="3" class="text-sm-right"><b>Full name: </b></b-col>
          <b-col>{{ row.item.firstName +" "+ row.item.lastName }}</b-col>
        </b-row>
        <b-row class="mb-2">
          <b-col sm="3" class="text-sm-right"><b>Birth date: </b></b-col>
          <b-col>{{ row.item.birthDate }}</b-col>
        </b-row>
        <b-row class="mb-2">
          <b-col sm="3" class="text-sm-right"><b>Employed: </b></b-col>
          <b-col>{{ row.item.Employed == 0 ? 'Yes' : 'No' }}</b-col>
        </b-row>
        <b-row class="mb-2">
          <b-col sm="3" class="text-sm-right"><b>Salary: </b></b-col>
          <b-col>{{"€ "+row.item.salary }}</b-col>
          </b-row>
      </b-card>
    </template>
    </b-table>

    <b-modal id="modalInfo" @hide="resetModal" :title="modalInfo.title" ok-only>
      <pre>{{modalInfo.content}}</pre>
    </b-modal>

    <b-modal id="modalDelete" title="Delete candidate">Are you sure?</b-modal>
</div>
    `
});
