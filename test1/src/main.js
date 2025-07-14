import Vue from 'vue'
import ViewUl from'view-design'
import App from './App.vue'
import'view-design/dist/styles/iview.css'
Vue.config.productionTip = false
Vue.use(ViewUl)
new Vue({
  render: h => h(App),
}).$mount('#app')
