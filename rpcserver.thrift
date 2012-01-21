/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements. See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership. The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/**
 * This Thrift file can be included by other Thrift files that want to share
 * these definitions.
 */

namespace py playrix.powerDNS
namespace py.twisted playrix.powerDNS

service BackendComunicateProxy
{
	bool add_domain(1: string dname, 2: i32 ttl);
	bool rmv_domain(1: string dname);
	bool add_domain_backet(1: string dname, 2: string bdname, 3: double longitude, 4: double latitude, 5: bool isdefault=false);
	bool rmv_domain_backet(1: string dname);
	bool add_domain_ip(1: string dname, 2: string bdname, 3: string ip);
	bool rmv_domain_ip(1: string dname, 2: string bdname, 3: string ip);
}
