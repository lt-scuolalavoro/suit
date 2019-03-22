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
      options: [
        {text: 'Show all', value: 'all'}, 
        {text: 'Show deleted candidates', value: 'deleted', disabled: false}
      ],
      fields: [
        { key: "firstName", sortable: true, label: "First name" },
        { key: "lastName", sortable: true, label: "Last name" },
        { key: "birthDate", label: "Birth date" },
        { key: "salary", sortable: true, label: "Salary" },
        { key: "action", label: "Actions" }
      ],
      modalInfo: { title: "", content: "" },
      idToRemove: 0,
    };
  },
  methods: {
    applyFilter(checked) {
      this.condition="";
      if(checked.includes("all")) {
        this.condition+="a";
        this.options[1].disabled=true;
      } else {
        this.options[1].disabled=false;
      }
      if(checked.includes("deleted")) {
        this.condition+="d";
      }
      this.typeSearch();
    },
    removeCandidate(){
      axios
        .post("cgi/removeCandidate.cgi", {
            id: this.idToRemove
        })
        .then(() => location.reload())
    },
    showModalInfo(button) {
      this.modalInfo.content = "Hello";
      this.$root.$emit("bv::show::modal", "modalInfo", button);
    },
    showModalDelete(button, row) {
      this.$root.$emit("bv::show::modal", "modalDelete", button);
      this.idToRemove = row.item.id;
    },
    resetModal() {
      this.modalInfo.title = "";
      this.modalInfo.content = "";
    },
    colorRows(){
      let i
      n = this.items.length
      for(i=0; i<n; i++){
        if(this.items[i].deleted=="1"){
          this.items[i]._rowVariant='danger'
        }else{
          if(this.items[i].employed=="1"){
            this.items[i]._rowVariant='success'
          }
        }
      }
    },
    setInitialSituation() {
      let i
      n = this.items.length
      this.filteredItems=[]
      for (i=0; i<n; i++) {
        if (this.items[i].deleted==0) {
          this.filteredItems.push(this.items[i]);
        }
      }
    },
    typeSearch(){
      let filteredList=[]
      let i
      let a=0;
      let d=0;
      let r=false;
      let r1=parseInt(this.range1);
      let r2=parseInt(this.range2);
      if (this.condition.includes("a")) {
        a=1;
      }
      if (this.condition.includes("d")) {
        d=1;
      }
      if (this.condition==="") {
        this.setInitialSituation();
      }
      if(r1<r2) {
        this.condition+="r";
        r=true;
      } else {
        this.condition=this.condition.replace('r', '');
      }
      if (this.condition==="") {
        this.setInitialSituation();
        if (this.filter!=="") {
          for (i=0; i<this.filteredItems.length; i++) {
            if(this.filteredItems[i].lastName.toLowerCase().includes(this.filter.toLowerCase()) || 
            this.filteredItems[i].firstName.toLowerCase().includes(this.filter.toLowerCase())){
              filteredList.push(this.filteredItems[i]);
            }
          }
          this.filteredItems=filteredList;
        }
      } else {
        for(i=0; i<this.items.length; i++){
          if(this.filter === "") {
            if (this.items[i].deleted==d) {
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
            if (a==1) {
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
              if (this.condition!=='') {
                if (this.items[i].deleted==d) {
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
                if (a==1) {
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
              }
            }
          }
        }
        this.filteredItems=filteredList;
      }
    }
  },
  mounted() {
    axios.get("cgi/candidates.cgi")
    .then(response => {
      this.items = response.data;
      this.setInitialSituation();
      this.colorRows();
    })
  },
  template: `
  <div>
  <b-row>
    <b-form-group class="mb-2 ml-4">
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
    <div>Salary:<br>
    Min: <b-form-input type="number" @input="typeSearch()" v-model="range1" min="0" size="sm" max="1000000"></b-form-input>
    Max: <b-form-input type="number" @input="typeSearch()" v-model="range2" min="0" size="sm" max="1000000"></b-form-input>
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
             :items="filteredItems"
             :fields="fields">

     <template slot="action" slot-scope="row">
         <b-button-group>
            <b-button variant="outline-primary" size="sm" @click.stop="row.toggleDetails"><i class="fas fa-ellipsis-v"></i></b-button>
            <b-button variant="outline-primary" onclick="location.href='user.html'" title="Edit candidate" size="sm"><i class="fas fa-pencil-alt"></i></b-button>
            <b-button @click.stop="showModalDelete(this, row)" variant="outline-danger" title="Delete candidate"size="sm"><i class="far fa-trash-alt"></i></b-button>
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
          <b-col>{{ row.item.employed == 1 ? 'Yes' : 'No' }}</b-col>
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

    <b-modal @ok="removeCandidate" id="modalDelete" title="Delete candidate">Are you sure?</b-modal>
</div>
    `
});
