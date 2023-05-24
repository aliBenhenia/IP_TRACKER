import React from 'react'
import axios from 'axios';
import { useState,useEffect } from 'react'

export default function Iptracker() {
  const [data,setData] = useState({});
  const [value, setValue] = useState('');
  const [location, setLocation] = useState({latt : 0, lang : 0});
  useEffect(() => {
    // async function fetchData() {
    //   const response = await axios.get('https://geo.ipify.org/api/v1', {
    //     params: {
    //       apiKey: 'at_oscZyeW32mODhkapBaVJRcKUiyBIo',
    //       ipAddress: value,
    //     },
    //   });
    //   setData(response.data);
    //   console.log(response.data)
    // }
    // fetchData();
        axios.get('https://geo.ipify.org/api/v1', {
            params: {
              apiKey: 'at_oscZyeW32mODhkapBaVJRcKUiyBIo',
              ipAddress: value,
          },
        })
        .then(response => {
            setData(response.data);
            const {lat,lng} = response.data.location;
            setLocation({latt : lat, lang : lng});
            console.log(response.data);
        })
        .catch(error => {
            console.error(error);
          });
  }, [value])
  const handInput = (e)=>{
    setValue(e.target.value)
  }
  // console.log(data)
  return (
    <div>
       <div className='cover p-4'>
          <h1 className='h3 text-white'>IP Address Tracker</h1>
          <div className='search'>
              <input
              value={value}
              onChange={handInput}
              className='p-2' type='text' placeholder='search for any ip or domain'/>
              <button 
              onClick={()=>alert(`your ip : ${value}`)}
              className='btn btn-dark ml-3'>
              <span className="material-symbols-outlined">
                chevron_right
              </span>
              </button>
          </div>
          <div className='info'>
            <div className='row'> 
              <div className='col-md-3'>
                <p>ip adress</p>
                <h6>{data.ip}</h6>
              </div>
              <div className='col-md-3'>
                <p>Location</p>
                <h6>{data.location.country} {data.location.city}</h6>
              </div>
              <div className='col-md-3'>
                <p>time zone</p>
                <h6>{data.location.timezone}</h6>
              </div>
              <div className='col-md-3'>
                <p>ISP</p>
                <h6>{data.isp}</h6>
              </div>
            </div>
          </div>
       </div>
      {/* <div id='map'> */}
         {/* <MyMaps  lat={location.lang} long={location.latt}/> */}
         {/* <Map  lat={location.lang} lng={location.latt} /> */}
      {/* </div> */}
    </div>
  )
}
