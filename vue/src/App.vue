<template>
  <div>
    <Space size="large">
      用户代码/姓名：
      <Input v-model="val" placeholder="Enter something..." style="width: 200px" />
      用户类型：
      <Select v-model="model" style="width:200px">
        <Option v-for="item in cityList" :value="item.value" :key="item.value">{{ item.label }}</Option>
      </Select>
      角色：
      <Select v-model="model" style="width:200px">
        <Option v-for="item in cityList" :value="item.value" :key="item.value">{{ item.label }}</Option>
      </Select>
      是否禁用：
      <Select v-model="model" style="width:200px">
        <Option v-for="item in cityList" :value="item.value" :key="item.value">{{ item.label }}</Option>
      </Select>
      <Button>查询</Button>
      <Button>重置</Button>
    </Space>
    <br>
    <Space size="large">
      <Button type="info">添加</Button>
      <Button type="warning">重置密码</Button>
    </Space>
    <div>
      <Table border ref="selection" :columns="columns" :data="data">
      <template #action="">
      <div>
        <Button type="warning">编辑</Button>
        <Button type="error">删除</Button>
        <Button type="info">重置密码</Button>
      </div>
    </template>
      </Table>
    </div>
    
  </div>
</template>

<script>
export default {
  data() {
    return {
      columns: [
        {
          type: 'selection',
          width: 60,
          align: 'center'
        },
        {
          title: '用户代码',
          key: 'name'
        },
        {
          title: '姓名',
          key: 'age'
        },
        {
          title: '用户类型',
          key: 'age'
        },
        {
          title: '是否禁用',
          render: (h, params) => {
            return h('i-switch', {
              props: {
                value: params.row.status,
                size: 'large'
              },
              scopedSlots: {
                open: () => h('span', '否'),
                close: () => h('span', '是')
              }
            })
          }
        },
        {
          title: 'Address',
          key: 'address'
        },
        {
          title: '操作aaa',
          slot: 'action'
                        
        },
      ],
      
      data: [
        {
          name: 'John Brown',
          age: 18,
          address: 'New York No. 1 Lake Park',
          date: '2016-10-03'
        },
        {
          name: 'Jim Green',
          age: 24,
          address: 'London No. 1 Lake Park',
          date: '2016-10-01'
        },
        {
          name: 'Joe Black',
          age: 30,
          address: 'Sydney No. 1 Lake Park',
          date: '2016-10-02'
        },
        {
          name: 'Jon Snow',
          age: 26,
          address: 'Ottawa No. 2 Lake Park',
          date: '2016-10-04'
        }
      ],
      val: '',
      cityList: [
        {
          value: 'New York',
          label: 'New York'
        },
        {
          value: 'London',
          label: 'London'
        },
        {
          value: 'Sydney',
          label: 'Sydney'
        },
        {
          value: 'Ottawa',
          label: 'Ottawa'
        },
        {
          value: 'Paris',
          label: 'Paris'
        },
        {
          value: 'Canberra',
          label: 'Canberra'
        }
      ],
    }
  }
}
</script>
