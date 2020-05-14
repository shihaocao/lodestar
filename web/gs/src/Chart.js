import React from 'react'
import ReactDOM from 'react-dom'

import {Line} from 'react-chartjs-2'

export default  class Chart extends React.Component {

  constructor(props)
  {
      super(props)
      this.buffersize

      this.data = {
        labels: [],
        datasets: [
          {
            label: 'My Chart',
            data: []
          }
        ]
      }

  }

  onChange(newdata) {

    const size = this.data.datasets[0].data.length
    if (size >= this.buffersize)
    {
      this.data.datasets[0].data.shift()
      this.data.labels.shift()
    }

    this.data.labels.push(newdata.label)
    this.data.datasets[0].data.push(newdata.value)

  }

  render()
  {
    return (
      <Line data={this.data}/>
    )
  }

}