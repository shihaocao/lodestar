import React, { useState, useEffect, useRef} from 'react';
import { useTheme } from '@material-ui/core/styles';
import { LineChart, Line, XAxis, YAxis, Label, ResponsiveContainer } from 'recharts';
import Title from './Title';

// Generate Sales Data
function createData(time, amount) {
  return { time, amount };
}

const data1 = [
  createData('00:00', 0),
  createData('03:00', 300),
  createData('06:00', 600),
  createData('09:00', 800),
  createData('12:00', 1500),
  createData('15:00', 2000),
  createData('18:00', 2400),
  createData('21:00', 2400),
  createData('24:00', undefined),
];

function interleave(times, vals){
  return times.reduce((acc, elem, i) => acc.concat(createData(elem, vals[i])),[]);
}

const data = [
  { name: '1', uv: -6.11 },
  { name: '2', uv: 0.39 },
  { name: '3', uv: -1.37 },
  { name: '4', uv: 1.16 },
  { name: '5', uv: 1.29 },
  { name: '6', uv: 0.09 },
  { name: '7', uv: 0.53 },
  { name: '8', uv: 2.52 },
  { name: '9', uv: 0.79 },
  { name: '10', uv: 2.94 },
  { name: '11', uv: 4.3 },
  { name: '12', uv: 7.41 },
  { name: '13', uv: -7.1 },
  { name: '14', uv: -1.17 },
  { name: '15', uv: -1.86 }
];

const initialState = {
  data,
  barIndex : 'uv',
  left : 0,
  right : 0
};

export default class Chart extends React.Component {

// export default function Chart() {

  // const t0 = [5,6,7,8]
  // const t1 = t0.map(x => x.toString())
  // const v2 = [40,50,23,55]

  // const [alts, setAlts] = useState(interleave(t1,v2));

  // // setAlts(interleave(t1,v2));

  // // useEffect(() => {
  // //   setAlts(interleave(t1,v2));
  // // }, []);


  // const update_graph = async () => {
  //   await fetch('/altitudes')
  //     .then(res => res.json())
  //     .then(data => {
      
      
  //     let alts_copy = alts;
  //     alts_copy.shift();
  //     // let alts_copy = alts.co();
  //     alts_copy.push(createData(data.cc, data.alt))
  //     console.log(alts_copy);
  //     setAlts(alts_copy);
  //   });
  // }

  // useEffect(() => {
  //   const interval = setInterval(() => {
  //     update_graph();
  //   }, 100);
  //   return () => clearInterval(interval);
  // }, []);


  constructor(props) {
    super(props);
    this.state = initialState;
    this.theme = useTheme();

  }
  
  handleChangeData(){  
        
		// shift
    this.setState( ( { data : cdata, left = 0 } ) => {
    	return { 
      	data : cdata.concat( { name : (cdata.length+1)+'', uv : 0} ), 
        animation : true, 
        left : left - 45
        };
    } );  

		// insert
    setTimeout( () => {
    	this.setState( ( { data : cdata } ) => {
    	  cdata[ cdata.length - 1 ].uv = parseInt(Math.random()*10 - 5, 10);
      	return { data : cdata.slice(), animation : true }
      } ); 
    }, 1200 );
  };

  render() {
  return (
    <React.Fragment>
      <Title>Today</Title>
      <ResponsiveContainer>
        <LineChart
          data={data}
          margin={{
            top: 16,
            right: 16,
            bottom: 0,
            left: 24,
          }}
        >
          <XAxis dataKey="time" stroke={this.theme.palette.text.secondary} />
          <YAxis stroke={this.theme.palette.text.secondary}>
            <Label
              angle={270}
              position="left"
              style={{ textAnchor: 'middle', fill: this.theme.palette.text.primary }}
            >
              Sales ($)
            </Label>
          </YAxis>
          <Line type="monotone" dataKey="amount" stroke={this.theme.palette.primary.main} dot={false} />
        </LineChart>
      </ResponsiveContainer>
    </React.Fragment>
  );
  }
}
